-- Partitioned version of the table; 25 partitions
-- start: 2450816, end: 2452822
-- delta: 80 or so
DROP TABLE IF EXISTS store_sales_25;
create table store_sales_25
(
    ss_sold_date_sk           integer                       ,
    ss_sold_time_sk           integer                       ,
    ss_item_sk                integer               ,
    ss_customer_sk            integer                       ,
    ss_cdemo_sk               integer                       ,
    ss_hdemo_sk               integer                       ,
    ss_addr_sk                integer                       ,
    ss_store_sk               integer                       ,
    ss_promo_sk               integer                       ,
    ss_ticket_number          bigint               ,
    ss_quantity               integer                       ,
    ss_wholesale_cost         decimal(7,2)                  ,
    ss_list_price             decimal(7,2)                  ,
    ss_sales_price            decimal(7,2)                  ,
    ss_ext_discount_amt       decimal(7,2)                  ,
    ss_ext_sales_price        decimal(7,2)                  ,
    ss_ext_wholesale_cost     decimal(7,2)                  ,
    ss_ext_list_price         decimal(7,2)                  ,
    ss_ext_tax                decimal(7,2)                  ,
    ss_coupon_amt             decimal(7,2)                  ,
    ss_net_paid               decimal(7,2)                  ,
    ss_net_paid_inc_tax       decimal(7,2)                  ,
    ss_net_profit             decimal(7,2)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (ss_item_sk, ss_ticket_number)
PARTITION BY RANGE (ss_sold_date_sk) (
  START (2450815) -- INCLUSIVE
  END (2452823) -- INCLUSIVE
  EVERY (80)
  WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ),
  DEFAULT PARTITION outlyers
);

/*
PARTITION BY RANGE (order_datetime) (
START (:DATA_START) END (:MONTHLY_END) EVERY (interval '1 month') WITH (appendonly=true, compresstype=quicklz, orientation=row)
*/
