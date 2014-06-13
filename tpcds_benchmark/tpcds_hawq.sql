-- 
-- Legal Notice 
-- 
-- This document and associated source code (the "Work") is a part of a 
-- benchmark specification maintained by the TPC. 
-- 
-- The TPC reserves all right, title, and interest to the Work as provided 
-- under U.S. and international laws, including without limitation all patent 
-- and trademark rights therein. 
-- 
-- No Warranty 
-- 
-- 1.1 TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THE INFORMATION 
--     CONTAINED HEREIN IS PROVIDED "AS IS" AND WITH ALL FAULTS, AND THE 
--     AUTHORS AND DEVELOPERS OF THE WORK HEREBY DISCLAIM ALL OTHER 
--     WARRANTIES AND CONDITIONS, EITHER EXPRESS, IMPLIED OR STATUTORY, 
--     INCLUDING, BUT NOT LIMITED TO, ANY (IF ANY) IMPLIED WARRANTIES, 
--     DUTIES OR CONDITIONS OF MERCHANTABILITY, OF FITNESS FOR A PARTICULAR 
--     PURPOSE, OF ACCURACY OR COMPLETENESS OF RESPONSES, OF RESULTS, OF 
--     WORKMANLIKE EFFORT, OF LACK OF VIRUSES, AND OF LACK OF NEGLIGENCE. 
--     ALSO, THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT, 
--     QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR NON-INFRINGEMENT 
--     WITH REGARD TO THE WORK. 
-- 1.2 IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THE WORK BE LIABLE TO 
--     ANY OTHER PARTY FOR ANY DAMAGES, INCLUDING BUT NOT LIMITED TO THE 
--     COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST PROFITS, LOSS 
--     OF USE, LOSS OF DATA, OR ANY INCIDENTAL, CONSEQUENTIAL, DIRECT, 
--     INDIRECT, OR SPECIAL DAMAGES WHETHER UNDER CONTRACT, TORT, WARRANTY,
--     OR OTHERWISE, ARISING IN ANY WAY OUT OF THIS OR ANY OTHER AGREEMENT 
--     RELATING TO THE WORK, WHETHER OR NOT SUCH AUTHOR OR DEVELOPER HAD 
--     ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. 
-- 
-- Contributors:
-- Gradient Systems
--
DROP TABLE IF EXISTS dbgen_version;
create table dbgen_version
(
    dv_version                varchar(16)                   ,
    dv_create_date            date                          ,
    dv_create_time            time                          ,
    dv_cmdline_args           varchar(200)
);

DROP TABLE IF EXISTS customer_address;
create table customer_address
(
    ca_address_sk             integer               ,
    ca_address_id             char(16)              ,
    ca_street_number          char(10)                      ,
    ca_street_name            varchar(60)                   ,
    ca_street_type            char(15)                      ,
    ca_suite_number           char(10)                      ,
    ca_city                   varchar(60)                   ,
    ca_county                 varchar(30)                   ,
    ca_state                  char(2)                       ,
    ca_zip                    char(10)                      ,
    ca_country                varchar(20)                   ,
    ca_gmt_offset             decimal(5,2)                  ,
    ca_location_type          char(20)                      
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (ca_address_sk);

DROP TABLE IF EXISTS customer_demographics;
create table customer_demographics
(
    cd_demo_sk                integer               ,
    cd_gender                 char(1)                       ,
    cd_marital_status         char(1)                       ,
    cd_education_status       char(20)                      ,
    cd_purchase_estimate      integer                       ,
    cd_credit_rating          char(10)                      ,
    cd_dep_count              integer                       ,
    cd_dep_employed_count     integer                       ,
    cd_dep_college_count      integer                       
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (cd_demo_sk);

DROP TABLE IF EXISTS date_dim;
create table date_dim
(
    d_date_sk                 integer               ,
    d_date_id                 char(16)              ,
    d_date                    date                          ,
    d_month_seq               integer                       ,
    d_week_seq                integer                       ,
    d_quarter_seq             integer                       ,
    d_year                    integer                       ,
    d_dow                     integer                       ,
    d_moy                     integer                       ,
    d_dom                     integer                       ,
    d_qoy                     integer                       ,
    d_fy_year                 integer                       ,
    d_fy_quarter_seq          integer                       ,
    d_fy_week_seq             integer                       ,
    d_day_name                char(9)                       ,
    d_quarter_name            char(6)                       ,
    d_holiday                 char(1)                       ,
    d_weekend                 char(1)                       ,
    d_following_holiday       char(1)                       ,
    d_first_dom               integer                       ,
    d_last_dom                integer                       ,
    d_same_day_ly             integer                       ,
    d_same_day_lq             integer                       ,
    d_current_day             char(1)                       ,
    d_current_week            char(1)                       ,
    d_current_month           char(1)                       ,
    d_current_quarter         char(1)                       ,
    d_current_year            char(1)                       
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (d_date_sk);

DROP TABLE IF EXISTS warehouse;
create table warehouse
(
    w_warehouse_sk            integer               ,
    w_warehouse_id            char(16)              ,
    w_warehouse_name          varchar(20)                   ,
    w_warehouse_sq_ft         integer                       ,
    w_street_number           char(10)                      ,
    w_street_name             varchar(60)                   ,
    w_street_type             char(15)                      ,
    w_suite_number            char(10)                      ,
    w_city                    varchar(60)                   ,
    w_county                  varchar(30)                   ,
    w_state                   char(2)                       ,
    w_zip                     char(10)                      ,
    w_country                 varchar(20)                   ,
    w_gmt_offset              decimal(5,2)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (w_warehouse_sk);

DROP TABLE IF EXISTS ship_mode;
create table ship_mode
(
    sm_ship_mode_sk           integer               ,
    sm_ship_mode_id           char(16)              ,
    sm_type                   char(30)                      ,
    sm_code                   char(10)                      ,
    sm_carrier                char(20)                      ,
    sm_contract               char(20)                      
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (sm_ship_mode_sk);

DROP TABLE IF EXISTS time_dim;
create table time_dim
(
    t_time_sk                 integer               ,
    t_time_id                 char(16)              ,
    t_time                    integer                       ,
    t_hour                    integer                       ,
    t_minute                  integer                       ,
    t_second                  integer                       ,
    t_am_pm                   char(2)                       ,
    t_shift                   char(20)                      ,
    t_sub_shift               char(20)                      ,
    t_meal_time               char(20)                      
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (t_time_sk);

DROP TABLE IF EXISTS reason;
create table reason
(
    r_reason_sk               integer               ,
    r_reason_id               char(16)              ,
    r_reason_desc             char(100)                     
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (r_reason_sk);

DROP TABLE IF EXISTS income_band;
create table income_band
(
    ib_income_band_sk         integer               ,
    ib_lower_bound            integer                       ,
    ib_upper_bound            integer                       
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (ib_income_band_sk);

DROP TABLE IF EXISTS item;
create table item
(
    i_item_sk                 integer               ,
    i_item_id                 char(16)              ,
    i_rec_start_date          date                          ,
    i_rec_end_date            date                          ,
    i_item_desc               varchar(200)                  ,
    i_current_price           decimal(7,2)                  ,
    i_wholesale_cost          decimal(7,2)                  ,
    i_brand_id                integer                       ,
    i_brand                   char(50)                      ,
    i_class_id                integer                       ,
    i_class                   char(50)                      ,
    i_category_id             integer                       ,
    i_category                char(50)                      ,
    i_manufact_id             integer                       ,
    i_manufact                char(50)                      ,
    i_size                    char(20)                      ,
    i_formulation             char(20)                      ,
    i_color                   char(20)                      ,
    i_units                   char(10)                      ,
    i_container               char(10)                      ,
    i_manager_id              integer                       ,
    i_product_name            char(50)                      
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (i_item_sk);

DROP TABLE IF EXISTS store;
create table store
(
    s_store_sk                integer               ,
    s_store_id                char(16)              ,
    s_rec_start_date          date                          ,
    s_rec_end_date            date                          ,
    s_closed_date_sk          integer                       ,
    s_store_name              varchar(50)                   ,
    s_number_employees        integer                       ,
    s_floor_space             integer                       ,
    s_hours                   char(20)                      ,
    s_manager                 varchar(40)                   ,
    s_market_id               integer                       ,
    s_geography_class         varchar(100)                  ,
    s_market_desc             varchar(100)                  ,
    s_market_manager          varchar(40)                   ,
    s_division_id             integer                       ,
    s_division_name           varchar(50)                   ,
    s_company_id              integer                       ,
    s_company_name            varchar(50)                   ,
    s_street_number           varchar(10)                   ,
    s_street_name             varchar(60)                   ,
    s_street_type             char(15)                      ,
    s_suite_number            char(10)                      ,
    s_city                    varchar(60)                   ,
    s_county                  varchar(30)                   ,
    s_state                   char(2)                       ,
    s_zip                     char(10)                      ,
    s_country                 varchar(20)                   ,
    s_gmt_offset              decimal(5,2)                  ,
    s_tax_precentage          decimal(5,2)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (s_store_sk);

DROP TABLE IF EXISTS call_center;
create table call_center
(
    cc_call_center_sk         integer               ,
    cc_call_center_id         char(16)              ,
    cc_rec_start_date         date                          ,
    cc_rec_end_date           date                          ,
    cc_closed_date_sk         integer                       ,
    cc_open_date_sk           integer                       ,
    cc_name                   varchar(50)                   ,
    cc_class                  varchar(50)                   ,
    cc_employees              integer                       ,
    cc_sq_ft                  integer                       ,
    cc_hours                  char(20)                      ,
    cc_manager                varchar(40)                   ,
    cc_mkt_id                 integer                       ,
    cc_mkt_class              char(50)                      ,
    cc_mkt_desc               varchar(100)                  ,
    cc_market_manager         varchar(40)                   ,
    cc_division               integer                       ,
    cc_division_name          varchar(50)                   ,
    cc_company                integer                       ,
    cc_company_name           char(50)                      ,
    cc_street_number          char(10)                      ,
    cc_street_name            varchar(60)                   ,
    cc_street_type            char(15)                      ,
    cc_suite_number           char(10)                      ,
    cc_city                   varchar(60)                   ,
    cc_county                 varchar(30)                   ,
    cc_state                  char(2)                       ,
    cc_zip                    char(10)                      ,
    cc_country                varchar(20)                   ,
    cc_gmt_offset             decimal(5,2)                  ,
    cc_tax_percentage         decimal(5,2)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (cc_call_center_sk);

DROP TABLE IF EXISTS customer;
create table customer
(
    c_customer_sk             integer               ,
    c_customer_id             char(16)              ,
    c_current_cdemo_sk        integer                       ,
    c_current_hdemo_sk        integer                       ,
    c_current_addr_sk         integer                       ,
    c_first_shipto_date_sk    integer                       ,
    c_first_sales_date_sk     integer                       ,
    c_salutation              char(10)                      ,
    c_first_name              char(20)                      ,
    c_last_name               char(30)                      ,
    c_preferred_cust_flag     char(1)                       ,
    c_birth_day               integer                       ,
    c_birth_month             integer                       ,
    c_birth_year              integer                       ,
    c_birth_country           varchar(20)                   ,
    c_login                   char(13)                      ,
    c_email_address           char(50)                      ,
    c_last_review_date        char(10)                      
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (c_customer_sk);

DROP TABLE IF EXISTS web_site;
create table web_site
(
    web_site_sk               integer               ,
    web_site_id               char(16)              ,
    web_rec_start_date        date                          ,
    web_rec_end_date          date                          ,
    web_name                  varchar(50)                   ,
    web_open_date_sk          integer                       ,
    web_close_date_sk         integer                       ,
    web_class                 varchar(50)                   ,
    web_manager               varchar(40)                   ,
    web_mkt_id                integer                       ,
    web_mkt_class             varchar(50)                   ,
    web_mkt_desc              varchar(100)                  ,
    web_market_manager        varchar(40)                   ,
    web_company_id            integer                       ,
    web_company_name          char(50)                      ,
    web_street_number         char(10)                      ,
    web_street_name           varchar(60)                   ,
    web_street_type           char(15)                      ,
    web_suite_number          char(10)                      ,
    web_city                  varchar(60)                   ,
    web_county                varchar(30)                   ,
    web_state                 char(2)                       ,
    web_zip                   char(10)                      ,
    web_country               varchar(20)                   ,
    web_gmt_offset            decimal(5,2)                  ,
    web_tax_percentage        decimal(5,2)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (web_site_sk);

DROP TABLE IF EXISTS store_returns;
create table store_returns
(
    sr_returned_date_sk       integer                       ,
    sr_return_time_sk         integer                       ,
    sr_item_sk                integer               ,
    sr_customer_sk            integer                       ,
    sr_cdemo_sk               integer                       ,
    sr_hdemo_sk               integer                       ,
    sr_addr_sk                integer                       ,
    sr_store_sk               integer                       ,
    sr_reason_sk              integer                       ,
    sr_ticket_number          bigint               ,
    sr_return_quantity        integer                       ,
    sr_return_amt             decimal(7,2)                  ,
    sr_return_tax             decimal(7,2)                  ,
    sr_return_amt_inc_tax     decimal(7,2)                  ,
    sr_fee                    decimal(7,2)                  ,
    sr_return_ship_cost       decimal(7,2)                  ,
    sr_refunded_cash          decimal(7,2)                  ,
    sr_reversed_charge        decimal(7,2)                  ,
    sr_store_credit           decimal(7,2)                  ,
    sr_net_loss               decimal(7,2)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (sr_item_sk, sr_ticket_number);

DROP TABLE IF EXISTS household_demographics;
create table household_demographics
(
    hd_demo_sk                integer               ,
    hd_income_band_sk         integer                       ,
    hd_buy_potential          char(15)                      ,
    hd_dep_count              integer                       ,
    hd_vehicle_count          integer                       
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (hd_demo_sk);

DROP TABLE IF EXISTS web_page;
create table web_page
(
    wp_web_page_sk            integer               ,
    wp_web_page_id            char(16)              ,
    wp_rec_start_date         date                          ,
    wp_rec_end_date           date                          ,
    wp_creation_date_sk       integer                       ,
    wp_access_date_sk         integer                       ,
    wp_autogen_flag           char(1)                       ,
    wp_customer_sk            integer                       ,
    wp_url                    varchar(100)                  ,
    wp_type                   char(50)                      ,
    wp_char_count             integer                       ,
    wp_link_count             integer                       ,
    wp_image_count            integer                       ,
    wp_max_ad_count           integer                       
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (wp_web_page_sk);

DROP TABLE IF EXISTS promotion;
create table promotion
(
    p_promo_sk                integer               ,
    p_promo_id                char(16)              ,
    p_start_date_sk           integer                       ,
    p_end_date_sk             integer                       ,
    p_item_sk                 integer                       ,
    p_cost                    decimal(15,2)                 ,
    p_response_target         integer                       ,
    p_promo_name              char(50)                      ,
    p_channel_dmail           char(1)                       ,
    p_channel_email           char(1)                       ,
    p_channel_catalog         char(1)                       ,
    p_channel_tv              char(1)                       ,
    p_channel_radio           char(1)                       ,
    p_channel_press           char(1)                       ,
    p_channel_event           char(1)                       ,
    p_channel_demo            char(1)                       ,
    p_channel_details         varchar(100)                  ,
    p_purpose                 char(15)                      ,
    p_discount_active         char(1)                       
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (p_promo_sk);

DROP TABLE IF EXISTS catalog_page;
create table catalog_page
(
    cp_catalog_page_sk        integer               ,
    cp_catalog_page_id        char(16)              ,
    cp_start_date_sk          integer                       ,
    cp_end_date_sk            integer                       ,
    cp_department             varchar(50)                   ,
    cp_catalog_number         integer                       ,
    cp_catalog_page_number    integer                       ,
    cp_description            varchar(100)                  ,
    cp_type                   varchar(100)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (cp_catalog_page_sk);

DROP TABLE IF EXISTS inventory;
create table inventory
(
    inv_date_sk               integer               ,
    inv_item_sk               integer               ,
    inv_warehouse_sk          integer               ,
    inv_quantity_on_hand      integer                       
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (inv_date_sk, inv_item_sk, inv_warehouse_sk);

DROP TABLE IF EXISTS catalog_returns;
create table catalog_returns
(
    cr_returned_date_sk       integer                       ,
    cr_returned_time_sk       integer                       ,
    cr_item_sk                integer               ,
    cr_refunded_customer_sk   integer                       ,
    cr_refunded_cdemo_sk      integer                       ,
    cr_refunded_hdemo_sk      integer                       ,
    cr_refunded_addr_sk       integer                       ,
    cr_returning_customer_sk  integer                       ,
    cr_returning_cdemo_sk     integer                       ,
    cr_returning_hdemo_sk     integer                       ,
    cr_returning_addr_sk      integer                       ,
    cr_call_center_sk         integer                       ,
    cr_catalog_page_sk        integer                       ,
    cr_ship_mode_sk           integer                       ,
    cr_warehouse_sk           integer                       ,
    cr_reason_sk              integer                       ,
    cr_order_number           bigint               ,
    cr_return_quantity        integer                       ,
    cr_return_amount          decimal(7,2)                  ,
    cr_return_tax             decimal(7,2)                  ,
    cr_return_amt_inc_tax     decimal(7,2)                  ,
    cr_fee                    decimal(7,2)                  ,
    cr_return_ship_cost       decimal(7,2)                  ,
    cr_refunded_cash          decimal(7,2)                  ,
    cr_reversed_charge        decimal(7,2)                  ,
    cr_store_credit           decimal(7,2)                  ,
    cr_net_loss               decimal(7,2)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (cr_item_sk, cr_order_number);

DROP TABLE IF EXISTS web_returns;
create table web_returns
(
    wr_returned_date_sk       integer                       ,
    wr_returned_time_sk       integer                       ,
    wr_item_sk                integer               ,
    wr_refunded_customer_sk   integer                       ,
    wr_refunded_cdemo_sk      integer                       ,
    wr_refunded_hdemo_sk      integer                       ,
    wr_refunded_addr_sk       integer                       ,
    wr_returning_customer_sk  integer                       ,
    wr_returning_cdemo_sk     integer                       ,
    wr_returning_hdemo_sk     integer                       ,
    wr_returning_addr_sk      integer                       ,
    wr_web_page_sk            integer                       ,
    wr_reason_sk              integer                       ,
    wr_order_number           bigint               ,
    wr_return_quantity        integer                       ,
    wr_return_amt             decimal(7,2)                  ,
    wr_return_tax             decimal(7,2)                  ,
    wr_return_amt_inc_tax     decimal(7,2)                  ,
    wr_fee                    decimal(7,2)                  ,
    wr_return_ship_cost       decimal(7,2)                  ,
    wr_refunded_cash          decimal(7,2)                  ,
    wr_reversed_charge        decimal(7,2)                  ,
    wr_account_credit         decimal(7,2)                  ,
    wr_net_loss               decimal(7,2)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (wr_item_sk, wr_order_number);

DROP TABLE IF EXISTS web_sales;
create table web_sales
(
    ws_sold_date_sk           integer                       ,
    ws_sold_time_sk           integer                       ,
    ws_ship_date_sk           integer                       ,
    ws_item_sk                integer               ,
    ws_bill_customer_sk       integer                       ,
    ws_bill_cdemo_sk          integer                       ,
    ws_bill_hdemo_sk          integer                       ,
    ws_bill_addr_sk           integer                       ,
    ws_ship_customer_sk       integer                       ,
    ws_ship_cdemo_sk          integer                       ,
    ws_ship_hdemo_sk          integer                       ,
    ws_ship_addr_sk           integer                       ,
    ws_web_page_sk            integer                       ,
    ws_web_site_sk            bigint                        ,
    ws_ship_mode_sk           integer                       ,
    ws_warehouse_sk           decimal(7,2)                       ,
    ws_promo_sk               decimal(7,2)                       ,
    ws_order_number           decimal(18,2)               ,
    ws_quantity               decimal(7,2)                       ,
    ws_wholesale_cost         decimal(7,2)                  ,
    ws_list_price             decimal(7,2)                  ,
    ws_sales_price            decimal(7,2)                  ,
    ws_ext_discount_amt       decimal(7,2)                  ,
    ws_ext_sales_price        decimal(7,2)                  ,
    ws_ext_wholesale_cost     decimal(7,2)                  ,
    ws_ext_list_price         decimal(7,2)                  ,
    ws_ext_tax                decimal(7,2)                  ,
    ws_coupon_amt             decimal(7,2)                  ,
    ws_ext_ship_cost          decimal(7,2)                  ,
    ws_net_paid               decimal(7,2)                  ,
    ws_net_paid_inc_tax       decimal(7,2)                  ,
    ws_net_paid_inc_ship      decimal(7,2)                  ,
    ws_net_paid_inc_ship_tax  decimal(7,2)                  ,
    ws_net_profit             decimal(7,2)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (ws_item_sk, ws_order_number);

DROP TABLE IF EXISTS catalog_sales;
create table catalog_sales
(
    cs_sold_date_sk           integer                       ,
    cs_sold_time_sk           integer                       ,
    cs_ship_date_sk           integer                       ,
    cs_bill_customer_sk       integer                       ,
    cs_bill_cdemo_sk          integer                       ,
    cs_bill_hdemo_sk          integer                       ,
    cs_bill_addr_sk           integer                       ,
    cs_ship_customer_sk       integer                       ,
    cs_ship_cdemo_sk          integer                       ,
    cs_ship_hdemo_sk          integer                       ,
    cs_ship_addr_sk           integer                       ,
    cs_call_center_sk         integer                       ,
    cs_catalog_page_sk        integer                       ,
    cs_ship_mode_sk           integer                       ,
    cs_warehouse_sk           integer                       ,
    cs_item_sk                integer               ,
    cs_promo_sk               bigint                ,
    cs_order_number           bigint               ,
    cs_quantity               decimal(7,2)                       ,
    cs_wholesale_cost         decimal(7,2)                  ,
    cs_list_price             decimal(7,2)                  ,
    cs_sales_price            decimal(7,2)                  ,
    cs_ext_discount_amt       decimal(7,2)                  ,
    cs_ext_sales_price        decimal(7,2)                  ,
    cs_ext_wholesale_cost     decimal(7,2)                  ,
    cs_ext_list_price         decimal(7,2)                  ,
    cs_ext_tax                decimal(7,2)                  ,
    cs_coupon_amt             decimal(7,2)                  ,
    cs_ext_ship_cost          decimal(7,2)                  ,
    cs_net_paid               decimal(7,2)                  ,
    cs_net_paid_inc_tax       decimal(7,2)                  ,
    cs_net_paid_inc_ship      decimal(7,2)                  ,
    cs_net_paid_inc_ship_tax  decimal(7,2)                  ,
    cs_net_profit             decimal(7,2)                  
)
WITH (APPENDONLY=TRUE, COMPRESSTYPE=QUICKLZ)
DISTRIBUTED BY (cs_item_sk, cs_order_number);

DROP TABLE IF EXISTS store_sales;
create table store_sales
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
DISTRIBUTED BY (ss_item_sk, ss_ticket_number);

/* BEGIN EXTERNAL TABLES */

DROP EXTERNAL TABLE IF EXISTS ext_dbgen_version;
CREATE EXTERNAL WEB TABLE ext_dbgen_version
(
  LIKE dbgen_version
) EXECUTE '/tmp/wrap_dsdgen.sh dbgen_version' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_customer_address;
CREATE EXTERNAL WEB TABLE ext_customer_address
(
  LIKE customer_address
) EXECUTE '/tmp/wrap_dsdgen.sh customer_address' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_customer_demographics;
CREATE EXTERNAL WEB TABLE ext_customer_demographics
(
  LIKE customer_demographics
) EXECUTE '/tmp/wrap_dsdgen.sh customer_demographics' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_date_dim;
CREATE EXTERNAL WEB TABLE ext_date_dim
(
  LIKE date_dim
) EXECUTE '/tmp/wrap_dsdgen.sh date_dim' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_warehouse;
CREATE EXTERNAL WEB TABLE ext_warehouse
(
  LIKE warehouse
) EXECUTE '/tmp/wrap_dsdgen.sh warehouse' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_ship_mode;
CREATE EXTERNAL WEB TABLE ext_ship_mode
(
  LIKE ship_mode
) EXECUTE '/tmp/wrap_dsdgen.sh ship_mode' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_time_dim;
CREATE EXTERNAL WEB TABLE ext_time_dim
(
  LIKE time_dim
) EXECUTE '/tmp/wrap_dsdgen.sh time_dim' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_reason;
CREATE EXTERNAL WEB TABLE ext_reason
(
  LIKE reason
) EXECUTE '/tmp/wrap_dsdgen.sh reason' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_income_band;
CREATE EXTERNAL WEB TABLE ext_income_band
(
  LIKE income_band
) EXECUTE '/tmp/wrap_dsdgen.sh income_band' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_item;
CREATE EXTERNAL WEB TABLE ext_item
(
  LIKE item
) EXECUTE '/tmp/wrap_dsdgen.sh item' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_store;
CREATE EXTERNAL WEB TABLE ext_store
(
  LIKE store
) EXECUTE '/tmp/wrap_dsdgen.sh store' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_call_center;
CREATE EXTERNAL WEB TABLE ext_call_center
(
  LIKE call_center
) EXECUTE '/tmp/wrap_dsdgen.sh call_center' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_customer;
CREATE EXTERNAL WEB TABLE ext_customer
(
  LIKE customer
) EXECUTE '/tmp/wrap_dsdgen.sh customer' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_web_site;
CREATE EXTERNAL WEB TABLE ext_web_site
(
  LIKE web_site
) EXECUTE '/tmp/wrap_dsdgen.sh web_site' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_store_returns;
CREATE EXTERNAL WEB TABLE ext_store_returns
(
  LIKE store_returns
) EXECUTE '/tmp/wrap_dsdgen.sh store_returns' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_household_demographics;
CREATE EXTERNAL WEB TABLE ext_household_demographics
(
  LIKE household_demographics
) EXECUTE '/tmp/wrap_dsdgen.sh household_demographics' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_web_page;
CREATE EXTERNAL WEB TABLE ext_web_page
(
  LIKE web_page
) EXECUTE '/tmp/wrap_dsdgen.sh web_page' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_promotion;
CREATE EXTERNAL WEB TABLE ext_promotion
(
  LIKE promotion
) EXECUTE '/tmp/wrap_dsdgen.sh promotion' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_catalog_page;
CREATE EXTERNAL WEB TABLE ext_catalog_page
(
  LIKE catalog_page
) EXECUTE '/tmp/wrap_dsdgen.sh catalog_page' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_inventory;
CREATE EXTERNAL WEB TABLE ext_inventory
(
  LIKE inventory
) EXECUTE '/tmp/wrap_dsdgen.sh inventory' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_catalog_returns;
CREATE EXTERNAL WEB TABLE ext_catalog_returns
(
  LIKE catalog_returns
) EXECUTE '/tmp/wrap_dsdgen.sh catalog_returns' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_web_returns;
CREATE EXTERNAL WEB TABLE ext_web_returns
(
  LIKE web_returns
) EXECUTE '/tmp/wrap_dsdgen.sh web_returns' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_web_sales;
CREATE EXTERNAL WEB TABLE ext_web_sales
(
  LIKE web_sales
) EXECUTE '/tmp/wrap_dsdgen.sh web_sales' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_catalog_sales;
CREATE EXTERNAL WEB TABLE ext_catalog_sales
(
  LIKE catalog_sales
) EXECUTE '/tmp/wrap_dsdgen.sh catalog_sales' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

DROP EXTERNAL TABLE IF EXISTS ext_store_sales;
CREATE EXTERNAL WEB TABLE ext_store_sales
(
  LIKE store_sales
) EXECUTE '/tmp/wrap_dsdgen.sh store_sales' ON ALL
FORMAT 'TEXT' (DELIMITER '|' NULL E'' FILL MISSING FIELDS) ENCODING 'latin1'
SEGMENT REJECT LIMIT 1 PERCENT;

/* BEGIN INSERT STATEMENTS */

INSERT INTO dbgen_version SELECT * FROM ext_dbgen_version;
INSERT INTO customer_address SELECT * FROM ext_customer_address;
INSERT INTO customer_demographics SELECT * FROM ext_customer_demographics;
INSERT INTO date_dim SELECT * FROM ext_date_dim;
INSERT INTO warehouse SELECT * FROM ext_warehouse;
INSERT INTO ship_mode SELECT * FROM ext_ship_mode;
INSERT INTO time_dim SELECT * FROM ext_time_dim;
INSERT INTO reason SELECT * FROM ext_reason;
INSERT INTO income_band SELECT * FROM ext_income_band;
INSERT INTO item SELECT * FROM ext_item;
INSERT INTO store SELECT * FROM ext_store;
INSERT INTO call_center SELECT * FROM ext_call_center;
INSERT INTO customer SELECT * FROM ext_customer;
INSERT INTO web_site SELECT * FROM ext_web_site;
INSERT INTO store_returns SELECT * FROM ext_store_returns;
INSERT INTO household_demographics SELECT * FROM ext_household_demographics;
INSERT INTO web_page SELECT * FROM ext_web_page;
INSERT INTO promotion SELECT * FROM ext_promotion;
INSERT INTO catalog_page SELECT * FROM ext_catalog_page;
INSERT INTO inventory SELECT * FROM ext_inventory;
INSERT INTO catalog_returns SELECT * FROM ext_catalog_returns;
INSERT INTO web_returns SELECT * FROM ext_web_returns;
INSERT INTO web_sales SELECT * FROM ext_web_sales;
INSERT INTO catalog_sales SELECT * FROM ext_catalog_sales;
INSERT INTO store_sales SELECT * FROM ext_store_sales;


