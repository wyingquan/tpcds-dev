/*
* $Id: pricing.c,v 1.5 2006/06/02 19:25:04 jms Exp $
*
* This software contains proprietary and confidential information of Gradient
* Systems Inc.  By accepting transfer of this copy, Recipient agrees
* to retain this software in confidence, to prevent disclosure to others, and
* to make no use of this software other than that for which it was delivered.
* This is an unpublished copyright work Gradient Systems, Inc.  Execpt as
* permitted by federal law, 17 USC 117, copying is strictly prohibited.
*
* Gradient Systems Inc. CONFIDENTIAL - (Gradient Systems Inc. Confidential
* when combined with the aggregated modules for this product)
* OBJECT CODE ONLY SOURCE MATERIALS
* (C) COPYRIGHT Gradient Systems Inc. 1997 - 2001
*
* All Rights Reserved  
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF GRADIENT SYSTEMS, INC.
* The copyright notice above does not evidence any   
* actual or intended publication of such source code.
*
* Revision History
* ===================
* $Log: pricing.c,v $
* Revision 1.5  2006/06/02 19:25:04  jms
* add per-item ship cost to source catalog and web lineitems
*
* Revision 1.4  2005/11/06 22:01:12  jms
* first rework of source generation
*
* Revision 1.3  2005/10/31 19:28:44  jms
* changes to the source schema to move the views forward
*
* Revision 1.2  2004/11/24 23:54:18  jms
* correct unix/dos line termination
*
* Revision 1.1.1.1  2004/11/24 22:57:42  jms
* re-establish external server
*
* Revision 1.7  2004/08/25 23:52:54  jms
* port to LINUX after makefile changes
*
* Revision 1.6  2004/08/20 19:40:50  jms
* changes from August F-2-F
*
* Revision 1.5  2004/03/26 22:05:29  jms
* solaris porting issues
*
* Revision 1.4  2003/03/21 19:56:45  jms
* resync with code on laptap
*
* Revision 1.3  2002/08/16 23:24:22  jms
* complete linkage of catalog sales and returns and clean up parent child handling
*
* Revision 1.2  2002/07/27 00:08:48  jms
* merge of WAM10 changes from sriram and linkage of sales and returns
*
* Revision 1.1.2.5  2002/07/22 22:46:14  jms
* replacing missing changes to align with WAM 10
* corrections to set_pricing() to align with WAM 10
*
* Revision 1.1.2.4  2002/07/18 23:03:53  jms
* porting corrections
*
* Revision 1.1.2.3  2002/07/18 22:57:31  jms
* porting corrections
*
* Revision 1.1.2.2  2002/07/18 22:41:47  jms
* correcting comile errors that  appeared under AIX
*
* Revision 1.1.2.1  2002/07/18 22:05:23  jms
* isolating pricing calculations for the sales tables
*
*
*/
#include "config.h"
#include "porting.h"
#include <stdio.h>
#include "decimal.h"
#include "pricing.h"
#include "constants.h"
#include "columns.h"
#include "error_msg.h"
#include "dist.h"
#include "driver.h"
#include "genrand.h"
#include "w_web_sales.h"
#include "s_pline.h"

#define MAX_LIMIT	12
static ds_limits_t	aPriceLimits[MAX_LIMIT] =
{
	{CS_PRICING, CS_QUANTITY_MAX, CS_MARKUP_MAX, CS_DISCOUNT_MAX, CS_WHOLESALE_MAX, CS_COUPON_MAX},
	{SS_PRICING, SS_QUANTITY_MAX, SS_MARKUP_MAX, SS_DISCOUNT_MAX, SS_WHOLESALE_MAX, SS_COUPON_MAX},
	{WS_PRICING, WS_QUANTITY_MAX, WS_MARKUP_MAX, WS_DISCOUNT_MAX, WS_WHOLESALE_MAX, WS_COUPON_MAX},
	{CR_PRICING, CS_QUANTITY_MAX, CS_MARKUP_MAX, CS_DISCOUNT_MAX, CS_WHOLESALE_MAX, CS_COUPON_MAX},
	{SR_PRICING, SS_QUANTITY_MAX, SS_MARKUP_MAX, SS_DISCOUNT_MAX, SS_WHOLESALE_MAX, SS_COUPON_MAX},
	{WR_PRICING, WS_QUANTITY_MAX, WS_MARKUP_MAX, WS_DISCOUNT_MAX, WS_WHOLESALE_MAX, WS_COUPON_MAX},
	{S_PLINE_PRICING, WS_QUANTITY_MAX, WS_MARKUP_MAX, WS_DISCOUNT_MAX, WS_WHOLESALE_MAX, WS_COUPON_MAX},
	{S_CLIN_PRICING, WS_QUANTITY_MAX, WS_MARKUP_MAX, WS_DISCOUNT_MAX, WS_WHOLESALE_MAX, WS_COUPON_MAX},
	{S_WLIN_PRICING, WS_QUANTITY_MAX, WS_MARKUP_MAX, WS_DISCOUNT_MAX, WS_WHOLESALE_MAX, WS_COUPON_MAX},
	{S_SRET_PRICING, WS_QUANTITY_MAX, WS_MARKUP_MAX, WS_DISCOUNT_MAX, WS_WHOLESALE_MAX, WS_COUPON_MAX},
	{S_CRET_PRICING, WS_QUANTITY_MAX, WS_MARKUP_MAX, WS_DISCOUNT_MAX, WS_WHOLESALE_MAX, WS_COUPON_MAX},
	{S_WRET_PRICING, WS_QUANTITY_MAX, WS_MARKUP_MAX, WS_DISCOUNT_MAX, WS_WHOLESALE_MAX, WS_COUPON_MAX}

};

/*
* Routine: set_pricing(int nTabId, ds_pricing_t *pPricing)
* Purpose: handle the various pricing calculations for the fact tables
* Notes:
*	the RNG usage is not kept in sync between sales pricing and returns pricing. If the calculations look wrong, it may 
*	be necessary to "waste" some RNG calls on one side or the other to bring things back in line
* Data Structures:
*
* Params:
* Returns:
* Called By: 
* Calls: 
* Assumptions:
* Side Effects:
* TODO: None
*/
void set_pricing(int nTabId, ds_pricing_t *pPricing)
{
	static int nLastId = -1, 
		init = 0,
		nQuantityMax,
		nQuantityMin = 1;
	static decimal_t dQuantity, dMarkupMin, dDiscountMin, dWholesaleMin,
		 dMarkupMax, dDiscountMax, dWholesaleMax, dCouponMin, dCouponMax,
		 dZero, dOneHalf, d9pct, dOne, dTemp, dHundred;
	decimal_t dMarkup, dCoupon, dShipping, dDiscount, dTemp2;
	int i,
		nCashPct,
		nCreditPct,
		nCouponUsage;
	
	if (!init)
	{
		strtodec(&dMarkupMin, "0.00");
		strtodec(&dDiscountMin, "0.00");
		strtodec(&dWholesaleMin, "1.00");
		strtodec(&dCouponMin, "0.00");
		strtodec(&dZero, "0.00");
		strtodec(&dOneHalf, "0.50");
		strtodec(&d9pct, "0.09");
		strtodec(&dWholesaleMin, "1.00");
		strtodec(&dHundred, "100.00");
		strtodec(&dOne, "1.00");

		init = 1;
	}
	
	if (nTabId != nLastId)
	{
		nLastId = -1;
		for (i=0; i < MAX_LIMIT; i++)
		{
			if (nTabId == aPriceLimits[i].nId)
				nLastId = i;
		}
		if (nLastId == -1)
			INTERNAL("No pricing limits defined");
		nQuantityMax = atoi(aPriceLimits[nLastId].szQuantity);
		strtodec(&dDiscountMax, aPriceLimits[nLastId].szDiscount);
		strtodec(&dMarkupMax, aPriceLimits[nLastId].szMarkUp);
		strtodec(&dWholesaleMax, aPriceLimits[nLastId].szWholesale);
		strtodec(&dCouponMax, aPriceLimits[nLastId].szCoupon);
	}

	switch(nTabId)
	{
	case SS_PRICING:
	case CS_PRICING:
	case WS_PRICING:
	case S_PLINE_PRICING:
	case S_CLIN_PRICING:
	case S_WLIN_PRICING:
		genrand_integer(&pPricing->quantity, DIST_UNIFORM, nQuantityMin, nQuantityMax, 0, nTabId);
		itodec(&dQuantity, pPricing->quantity);
		genrand_decimal(&pPricing->wholesale_cost, DIST_UNIFORM, &dWholesaleMin, &dWholesaleMax, NULL, nTabId);

		/* ext_wholesale_cost = wholesale_cost * quantity */
		decimal_t_op(&pPricing->ext_wholesale_cost, OP_MULT, &dQuantity, &pPricing->wholesale_cost);
		
		/* list_price = wholesale_cost * (1 + markup) */
		genrand_decimal(&dMarkup, DIST_UNIFORM, &dMarkupMin, &dMarkupMax, NULL, nTabId);
		decimal_t_op(&dMarkup, OP_PLUS, &dMarkup, &dOne);
		decimal_t_op(&pPricing->list_price, OP_MULT, &pPricing->wholesale_cost, &dMarkup);
		
		/* sales_price = list_price * (1 - discount)*/
		genrand_decimal(&dDiscount, DIST_UNIFORM, &dDiscountMin, &dDiscountMax, NULL, nTabId);
		NegateDecimal(&dDiscount);
		decimal_t_op(&pPricing->ext_discount_amt, OP_PLUS, &dDiscount, &dOne);
		decimal_t_op(&pPricing->sales_price, OP_MULT, &pPricing->list_price, &pPricing->ext_discount_amt);
		
		/* ext_list_price = list_price * quantity */
		decimal_t_op(&pPricing->ext_list_price, OP_MULT, &pPricing->list_price, &dQuantity);
		
		/* ext_sales_price = sales_price * quantity */
		decimal_t_op(&pPricing->ext_sales_price, OP_MULT, &pPricing->sales_price, &dQuantity);
		
		/* ext_discount_amt = ext_list_price - ext_sales_price */
		decimal_t_op(&pPricing->ext_discount_amt, OP_MINUS, &pPricing->ext_list_price, &pPricing->ext_sales_price);
		
		/* coupon_amt = ext_sales_price * coupon */
		genrand_decimal(&dCoupon, DIST_UNIFORM, &dZero, &dOne, NULL, nTabId);
		genrand_integer(&nCouponUsage, DIST_UNIFORM, 1, 100, 0, nTabId);
		if (nCouponUsage <= 20)	/* 20% of sales employ a coupon */
			decimal_t_op(&pPricing->coupon_amt, OP_MULT, &pPricing->ext_sales_price, &dCoupon);
		else
			memcpy(&pPricing->coupon_amt, &dZero, sizeof(decimal_t));
		
		/* net_paid = ext_sales_price - coupon_amt */
		decimal_t_op(&pPricing->net_paid, OP_MINUS, &pPricing->ext_sales_price, &pPricing->coupon_amt);
		
		/* shipping_cost = list_price * shipping */
		genrand_decimal(&dShipping, DIST_UNIFORM, &dZero, &dOneHalf, NULL, nTabId);
		decimal_t_op(&pPricing->ship_cost, OP_MULT, &pPricing->list_price, &dShipping);

      /* ext_shipping_cost = shipping_cost * quantity */
		decimal_t_op(&pPricing->ext_ship_cost, OP_MULT, &pPricing->ship_cost, &dQuantity);
		
		/* net_paid_inc_ship = net_paid + ext_shipping_cost */
		decimal_t_op(&pPricing->net_paid_inc_ship, OP_PLUS, &pPricing->net_paid, &pPricing->ext_ship_cost);
		
		/* ext_tax = tax * net_paid */
		genrand_decimal(&pPricing->tax_pct, DIST_UNIFORM, &dZero, &d9pct, NULL, nTabId);
		decimal_t_op(&pPricing->ext_tax, OP_MULT, &pPricing->net_paid, &pPricing->tax_pct);
		
		/* net_paid_inc_tax = net_paid + ext_tax */
		decimal_t_op(&pPricing->net_paid_inc_tax, OP_PLUS, &pPricing->net_paid, &pPricing->ext_tax);
		
		/* net_paid_inc_ship_tax = net_paid_inc_tax + ext_shipping_cost */
		decimal_t_op(&pPricing->net_paid_inc_ship_tax, OP_PLUS, &pPricing->net_paid_inc_ship, &pPricing->ext_tax);
		
		/* net_profit = net_paid - ext_wholesale_cost */
		decimal_t_op(&pPricing->net_profit, OP_MINUS, &pPricing->net_paid, &pPricing->ext_wholesale_cost);
		break;
	case CR_PRICING:
	case SR_PRICING:
	case WR_PRICING:
		/* quantity is determined before we are called */
		/* ext_wholesale_cost = wholesale_cost * quantity */
		itodec(&dQuantity, pPricing->quantity);
		decimal_t_op(&pPricing->ext_wholesale_cost, OP_MULT, &dQuantity, &pPricing->wholesale_cost);
		
		/* ext_list_price = list_price * quantity */
		decimal_t_op(&pPricing->ext_list_price, OP_MULT, &pPricing->list_price, &dQuantity);
		
		/* ext_sales_price = sales_price * quantity */
		decimal_t_op(&pPricing->ext_sales_price, OP_MULT, &pPricing->sales_price, &dQuantity);
		
		/* net_paid = ext_list_price (couppons don't effect returns) */
		memcpy(&pPricing->net_paid, &pPricing->ext_sales_price, sizeof(decimal_t));
		
		/* shipping_cost = list_price * shipping */
		genrand_decimal(&dShipping, DIST_UNIFORM, &dZero, &dOneHalf, NULL, nTabId);
		decimal_t_op(&pPricing->ship_cost, OP_MULT, &pPricing->list_price, &dShipping);

      /* ext_shipping_cost = shipping_cost * quantity */
		decimal_t_op(&pPricing->ext_ship_cost, OP_MULT, &pPricing->ship_cost, &dQuantity);
				
		/* net_paid_inc_ship = net_paid + ext_shipping_cost */
		decimal_t_op(&pPricing->net_paid_inc_ship, OP_PLUS, &pPricing->net_paid, &pPricing->ext_ship_cost);
		
		/* ext_tax = tax * net_paid */
		decimal_t_op(&pPricing->ext_tax, OP_MULT, &pPricing->net_paid, &pPricing->tax_pct);
		
		/* net_paid_inc_tax = net_paid + ext_tax */
		decimal_t_op(&pPricing->net_paid_inc_tax, OP_PLUS, &pPricing->net_paid, &pPricing->ext_tax);
		
		/* net_paid_inc_ship_tax = net_paid_inc_tax + ext_shipping_cost */
		decimal_t_op(&pPricing->net_paid_inc_ship_tax, OP_PLUS, &pPricing->net_paid_inc_ship, &pPricing->ext_tax);
		
		/* net_profit = net_paid - ext_wholesale_cost */
		decimal_t_op(&pPricing->net_profit, OP_MINUS, &pPricing->net_paid, &pPricing->ext_wholesale_cost);
		
		/* see to it that the returned amounts add up to the total returned */
		/* allocate some of return to cash */
		genrand_integer(&nCashPct, DIST_UNIFORM, 0, 100, 0, nTabId);
		itodec(&dTemp, nCashPct);
		decimal_t_op(&pPricing->refunded_cash, OP_DIV, &dTemp, &dHundred);
		decimal_t_op(&pPricing->refunded_cash, OP_MULT, &pPricing->refunded_cash, &pPricing->net_paid);
		
		/* allocate some to reversed charges */
		genrand_integer(&nCreditPct, DIST_UNIFORM, 1, 100, 0, nTabId);
		itodec(&dTemp2, nCreditPct);
		decimal_t_op(&dTemp, OP_DIV, &dTemp2, &dHundred);
		decimal_t_op(&dTemp2, OP_MINUS, &pPricing->net_paid, &pPricing->refunded_cash);
		decimal_t_op(&pPricing->reversed_charge, OP_MULT, &dTemp2, &dTemp);
		
		/* the rest is store credit */
		decimal_t_op(&pPricing->store_credit, OP_MINUS, &pPricing->net_paid, &pPricing->reversed_charge);
		decimal_t_op(&pPricing->store_credit, OP_MINUS, &pPricing->store_credit, &pPricing->refunded_cash);
		
		/* pick a fee for the return */
		genrand_decimal(&pPricing->fee, DIST_UNIFORM, &dOneHalf, &dHundred, &dZero, nTabId);
		
		/* and calculate the net effect */
		decimal_t_op(&pPricing->net_loss, OP_MINUS, &pPricing->net_paid_inc_ship_tax, &pPricing->store_credit);
		decimal_t_op(&pPricing->net_loss, OP_MINUS, &pPricing->net_loss, &pPricing->refunded_cash);
		decimal_t_op(&pPricing->net_loss, OP_MINUS, &pPricing->net_loss, &pPricing->reversed_charge);
		decimal_t_op(&pPricing->net_loss, OP_PLUS, &pPricing->net_loss, &pPricing->fee);
		break;
	}

	return;

}







