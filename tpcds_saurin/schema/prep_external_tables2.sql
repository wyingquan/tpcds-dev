DROP EXTERNAL TABLE IF EXISTS customer_address_ext;
CREATE EXTERNAL TABLE customer_address_ext
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
LOCATION('gpfdist://sdw10:21567/customer_address_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS customer_demographics_ext;
CREATE EXTERNAL TABLE customer_demographics_ext
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
LOCATION('gpfdist://sdw10:21567/customer_demographics_4_32.dat','gpfdist://sdw10:21567/customer_demographics_2_32.dat','gpfdist://sdw10:21567/customer_demographics_3_32.dat','gpfdist://sdw10:21567/customer_demographics_1_32.dat','gpfdist://sdw11:21567/customer_demographics_5_32.dat','gpfdist://sdw11:21567/customer_demographics_6_32.dat','gpfdist://sdw11:21567/customer_demographics_8_32.dat','gpfdist://sdw11:21567/customer_demographics_7_32.dat','gpfdist://sdw12:21567/customer_demographics_9_32.dat','gpfdist://sdw12:21567/customer_demographics_11_32.dat','gpfdist://sdw12:21567/customer_demographics_12_32.dat','gpfdist://sdw12:21567/customer_demographics_10_32.dat','gpfdist://sdw13:21567/customer_demographics_15_32.dat','gpfdist://sdw13:21567/customer_demographics_14_32.dat','gpfdist://sdw13:21567/customer_demographics_16_32.dat','gpfdist://sdw13:21567/customer_demographics_13_32.dat','gpfdist://sdw14:21567/customer_demographics_20_32.dat','gpfdist://sdw14:21567/customer_demographics_18_32.dat','gpfdist://sdw14:21567/customer_demographics_19_32.dat','gpfdist://sdw14:21567/customer_demographics_17_32.dat','gpfdist://sdw15:21567/customer_demographics_22_32.dat','gpfdist://sdw15:21567/customer_demographics_23_32.dat','gpfdist://sdw15:21567/customer_demographics_21_32.dat','gpfdist://sdw15:21567/customer_demographics_24_32.dat','gpfdist://sdw16:21567/customer_demographics_28_32.dat','gpfdist://sdw16:21567/customer_demographics_25_32.dat','gpfdist://sdw16:21567/customer_demographics_27_32.dat','gpfdist://sdw16:21567/customer_demographics_26_32.dat','gpfdist://sdw9:21567/customer_demographics_31_32.dat','gpfdist://sdw9:21567/customer_demographics_32_32.dat','gpfdist://sdw9:21567/customer_demographics_29_32.dat','gpfdist://sdw9:21567/customer_demographics_30_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS date_dim_ext;
CREATE EXTERNAL TABLE date_dim_ext
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
LOCATION('gpfdist://sdw10:21567/date_dim_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS warehouse_ext;
CREATE EXTERNAL TABLE warehouse_ext
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
LOCATION('gpfdist://sdw10:21567/warehouse_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS ship_mode_ext;
CREATE EXTERNAL TABLE ship_mode_ext
(
sm_ship_mode_sk           integer               ,
sm_ship_mode_id           char(16)              ,
sm_type                   char(30)                      ,
sm_code                   char(10)                      ,
sm_carrier                char(20)                      ,
sm_contract               char(20)
)
LOCATION('gpfdist://sdw10:21567/ship_mode_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS time_dim_ext;
CREATE EXTERNAL TABLE time_dim_ext
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
LOCATION('gpfdist://sdw10:21567/time_dim_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS reason_ext;
CREATE EXTERNAL TABLE reason_ext
(
r_reason_sk               integer               ,
r_reason_id               char(16)              ,
r_reason_desc             char(100)
)
LOCATION('gpfdist://sdw10:21567/reason_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS income_band_ext;
CREATE EXTERNAL TABLE income_band_ext
(
ib_income_band_sk         integer               ,
ib_lower_bound            integer                       ,
ib_upper_bound            integer
)
LOCATION('gpfdist://sdw10:21567/income_band_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS item_ext;
CREATE EXTERNAL TABLE item_ext
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
LOCATION('gpfdist://sdw10:21567/item_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS store_ext;
CREATE EXTERNAL TABLE store_ext
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
LOCATION('gpfdist://sdw10:21567/store_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS call_center_ext;
CREATE EXTERNAL TABLE call_center_ext
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
LOCATION('gpfdist://sdw10:21567/call_center_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS customer_ext;
CREATE EXTERNAL TABLE customer_ext
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
LOCATION('gpfdist://sdw10:21567/customer_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS web_site_ext;
CREATE EXTERNAL TABLE web_site_ext
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
LOCATION('gpfdist://sdw10:21567/web_site_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS store_returns_ext;
CREATE EXTERNAL TABLE store_returns_ext
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
LOCATION('gpfdist://sdw10:21567/store_returns_4_32.dat','gpfdist://sdw10:21567/store_returns_2_32.dat','gpfdist://sdw10:21567/store_returns_3_32.dat','gpfdist://sdw10:21567/store_returns_1_32.dat','gpfdist://sdw11:21567/store_returns_5_32.dat','gpfdist://sdw11:21567/store_returns_6_32.dat','gpfdist://sdw11:21567/store_returns_8_32.dat','gpfdist://sdw11:21567/store_returns_7_32.dat','gpfdist://sdw12:21567/store_returns_9_32.dat','gpfdist://sdw12:21567/store_returns_11_32.dat','gpfdist://sdw12:21567/store_returns_12_32.dat','gpfdist://sdw12:21567/store_returns_10_32.dat','gpfdist://sdw13:21567/store_returns_15_32.dat','gpfdist://sdw13:21567/store_returns_14_32.dat','gpfdist://sdw13:21567/store_returns_16_32.dat','gpfdist://sdw13:21567/store_returns_13_32.dat','gpfdist://sdw14:21567/store_returns_20_32.dat','gpfdist://sdw14:21567/store_returns_18_32.dat','gpfdist://sdw14:21567/store_returns_19_32.dat','gpfdist://sdw14:21567/store_returns_17_32.dat','gpfdist://sdw15:21567/store_returns_22_32.dat','gpfdist://sdw15:21567/store_returns_23_32.dat','gpfdist://sdw15:21567/store_returns_21_32.dat','gpfdist://sdw15:21567/store_returns_24_32.dat','gpfdist://sdw16:21567/store_returns_28_32.dat','gpfdist://sdw16:21567/store_returns_25_32.dat','gpfdist://sdw16:21567/store_returns_27_32.dat','gpfdist://sdw16:21567/store_returns_26_32.dat','gpfdist://sdw9:21567/store_returns_31_32.dat','gpfdist://sdw9:21567/store_returns_32_32.dat','gpfdist://sdw9:21567/store_returns_29_32.dat','gpfdist://sdw9:21567/store_returns_30_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS household_demographics_ext;
CREATE EXTERNAL TABLE household_demographics_ext
(
hd_demo_sk                integer               ,
hd_income_band_sk         integer                       ,
hd_buy_potential          char(15)                      ,
hd_dep_count              integer                       ,
hd_vehicle_count          integer
)
LOCATION('gpfdist://sdw10:21567/household_demographics_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS web_page_ext;
CREATE EXTERNAL TABLE web_page_ext
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
LOCATION('gpfdist://sdw10:21567/web_page_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS promotion_ext;
CREATE EXTERNAL TABLE promotion_ext
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
LOCATION('gpfdist://sdw10:21567/promotion_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS catalog_page_ext;
CREATE EXTERNAL TABLE catalog_page_ext
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
LOCATION('gpfdist://sdw10:21567/catalog_page_1_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS inventory_ext;
CREATE EXTERNAL TABLE inventory_ext
(
inv_date_sk               integer               ,
inv_item_sk               integer               ,
inv_warehouse_sk          integer               ,
inv_quantity_on_hand      integer
)
LOCATION('gpfdist://sdw10:21567/inventory_4_32.dat','gpfdist://sdw10:21567/inventory_2_32.dat','gpfdist://sdw10:21567/inventory_3_32.dat','gpfdist://sdw10:21567/inventory_1_32.dat','gpfdist://sdw11:21567/inventory_5_32.dat','gpfdist://sdw11:21567/inventory_6_32.dat','gpfdist://sdw11:21567/inventory_8_32.dat','gpfdist://sdw11:21567/inventory_7_32.dat','gpfdist://sdw12:21567/inventory_9_32.dat','gpfdist://sdw12:21567/inventory_11_32.dat','gpfdist://sdw12:21567/inventory_12_32.dat','gpfdist://sdw12:21567/inventory_10_32.dat','gpfdist://sdw13:21567/inventory_15_32.dat','gpfdist://sdw13:21567/inventory_14_32.dat','gpfdist://sdw13:21567/inventory_16_32.dat','gpfdist://sdw13:21567/inventory_13_32.dat','gpfdist://sdw14:21567/inventory_20_32.dat','gpfdist://sdw14:21567/inventory_18_32.dat','gpfdist://sdw14:21567/inventory_19_32.dat','gpfdist://sdw14:21567/inventory_17_32.dat','gpfdist://sdw15:21567/inventory_22_32.dat','gpfdist://sdw15:21567/inventory_23_32.dat','gpfdist://sdw15:21567/inventory_21_32.dat','gpfdist://sdw15:21567/inventory_24_32.dat','gpfdist://sdw16:21567/inventory_28_32.dat','gpfdist://sdw16:21567/inventory_25_32.dat','gpfdist://sdw16:21567/inventory_27_32.dat','gpfdist://sdw16:21567/inventory_26_32.dat','gpfdist://sdw9:21567/inventory_31_32.dat','gpfdist://sdw9:21567/inventory_32_32.dat','gpfdist://sdw9:21567/inventory_29_32.dat','gpfdist://sdw9:21567/inventory_30_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS catalog_returns_ext;
CREATE EXTERNAL TABLE catalog_returns_ext
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
LOCATION('gpfdist://sdw10:21567/catalog_returns_2_32.dat','gpfdist://sdw10:21567/catalog_returns_3_32.dat','gpfdist://sdw10:21567/catalog_returns_4_32.dat','gpfdist://sdw10:21567/catalog_returns_1_32.dat','gpfdist://sdw11:21567/catalog_returns_5_32.dat','gpfdist://sdw11:21567/catalog_returns_6_32.dat','gpfdist://sdw11:21567/catalog_returns_7_32.dat','gpfdist://sdw11:21567/catalog_returns_8_32.dat','gpfdist://sdw12:21567/catalog_returns_9_32.dat','gpfdist://sdw12:21567/catalog_returns_10_32.dat','gpfdist://sdw12:21567/catalog_returns_11_32.dat','gpfdist://sdw12:21567/catalog_returns_12_32.dat','gpfdist://sdw13:21567/catalog_returns_13_32.dat','gpfdist://sdw13:21567/catalog_returns_15_32.dat','gpfdist://sdw13:21567/catalog_returns_14_32.dat','gpfdist://sdw13:21567/catalog_returns_16_32.dat','gpfdist://sdw14:21567/catalog_returns_17_32.dat','gpfdist://sdw14:21567/catalog_returns_18_32.dat','gpfdist://sdw14:21567/catalog_returns_20_32.dat','gpfdist://sdw14:21567/catalog_returns_19_32.dat','gpfdist://sdw15:21567/catalog_returns_21_32.dat','gpfdist://sdw15:21567/catalog_returns_22_32.dat','gpfdist://sdw15:21567/catalog_returns_23_32.dat','gpfdist://sdw15:21567/catalog_returns_24_32.dat','gpfdist://sdw16:21567/catalog_returns_25_32.dat','gpfdist://sdw16:21567/catalog_returns_26_32.dat','gpfdist://sdw16:21567/catalog_returns_27_32.dat','gpfdist://sdw16:21567/catalog_returns_28_32.dat','gpfdist://sdw9:21567/catalog_returns_29_32.dat','gpfdist://sdw9:21567/catalog_returns_30_32.dat','gpfdist://sdw9:21567/catalog_returns_31_32.dat','gpfdist://sdw9:21567/catalog_returns_32_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS web_returns_ext;
CREATE EXTERNAL TABLE web_returns_ext
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
LOCATION('gpfdist://sdw10:21567/web_returns_4_32.dat','gpfdist://sdw10:21567/web_returns_3_32.dat','gpfdist://sdw10:21567/web_returns_2_32.dat','gpfdist://sdw10:21567/web_returns_1_32.dat','gpfdist://sdw11:21567/web_returns_5_32.dat','gpfdist://sdw11:21567/web_returns_6_32.dat','gpfdist://sdw11:21567/web_returns_8_32.dat','gpfdist://sdw11:21567/web_returns_7_32.dat','gpfdist://sdw12:21567/web_returns_9_32.dat','gpfdist://sdw12:21567/web_returns_12_32.dat','gpfdist://sdw12:21567/web_returns_11_32.dat','gpfdist://sdw12:21567/web_returns_10_32.dat','gpfdist://sdw13:21567/web_returns_15_32.dat','gpfdist://sdw13:21567/web_returns_14_32.dat','gpfdist://sdw13:21567/web_returns_16_32.dat','gpfdist://sdw13:21567/web_returns_13_32.dat','gpfdist://sdw14:21567/web_returns_20_32.dat','gpfdist://sdw14:21567/web_returns_18_32.dat','gpfdist://sdw14:21567/web_returns_19_32.dat','gpfdist://sdw14:21567/web_returns_17_32.dat','gpfdist://sdw15:21567/web_returns_23_32.dat','gpfdist://sdw15:21567/web_returns_22_32.dat','gpfdist://sdw15:21567/web_returns_21_32.dat','gpfdist://sdw15:21567/web_returns_24_32.dat','gpfdist://sdw16:21567/web_returns_28_32.dat','gpfdist://sdw16:21567/web_returns_25_32.dat','gpfdist://sdw16:21567/web_returns_27_32.dat','gpfdist://sdw16:21567/web_returns_26_32.dat','gpfdist://sdw9:21567/web_returns_31_32.dat','gpfdist://sdw9:21567/web_returns_32_32.dat','gpfdist://sdw9:21567/web_returns_29_32.dat','gpfdist://sdw9:21567/web_returns_30_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS web_sales_ext;
CREATE EXTERNAL TABLE web_sales_ext
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
ws_web_site_sk            integer                       ,
ws_ship_mode_sk           integer                       ,
ws_warehouse_sk           integer                       ,
ws_promo_sk               integer                       ,
ws_order_number           bigint               ,
ws_quantity               integer                       ,
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
LOCATION('gpfdist://sdw10:21567/web_sales_4_32.dat','gpfdist://sdw10:21567/web_sales_3_32.dat','gpfdist://sdw10:21567/web_sales_2_32.dat','gpfdist://sdw10:21567/web_sales_1_32.dat','gpfdist://sdw11:21567/web_sales_5_32.dat','gpfdist://sdw11:21567/web_sales_6_32.dat','gpfdist://sdw11:21567/web_sales_8_32.dat','gpfdist://sdw11:21567/web_sales_7_32.dat','gpfdist://sdw12:21567/web_sales_9_32.dat','gpfdist://sdw12:21567/web_sales_12_32.dat','gpfdist://sdw12:21567/web_sales_11_32.dat','gpfdist://sdw12:21567/web_sales_10_32.dat','gpfdist://sdw13:21567/web_sales_15_32.dat','gpfdist://sdw13:21567/web_sales_14_32.dat','gpfdist://sdw13:21567/web_sales_16_32.dat','gpfdist://sdw13:21567/web_sales_13_32.dat','gpfdist://sdw14:21567/web_sales_20_32.dat','gpfdist://sdw14:21567/web_sales_18_32.dat','gpfdist://sdw14:21567/web_sales_19_32.dat','gpfdist://sdw14:21567/web_sales_17_32.dat','gpfdist://sdw15:21567/web_sales_23_32.dat','gpfdist://sdw15:21567/web_sales_22_32.dat','gpfdist://sdw15:21567/web_sales_21_32.dat','gpfdist://sdw15:21567/web_sales_24_32.dat','gpfdist://sdw16:21567/web_sales_28_32.dat','gpfdist://sdw16:21567/web_sales_25_32.dat','gpfdist://sdw16:21567/web_sales_27_32.dat','gpfdist://sdw16:21567/web_sales_26_32.dat','gpfdist://sdw9:21567/web_sales_31_32.dat','gpfdist://sdw9:21567/web_sales_32_32.dat','gpfdist://sdw9:21567/web_sales_29_32.dat','gpfdist://sdw9:21567/web_sales_30_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS catalog_sales_ext;
CREATE EXTERNAL TABLE catalog_sales_ext
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
cs_promo_sk               integer                       ,
cs_order_number           bigint               ,
cs_quantity               integer                       ,
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
LOCATION('gpfdist://sdw10:21567/catalog_sales_2_32.dat','gpfdist://sdw10:21567/catalog_sales_3_32.dat','gpfdist://sdw10:21567/catalog_sales_4_32.dat','gpfdist://sdw10:21567/catalog_sales_1_32.dat','gpfdist://sdw11:21567/catalog_sales_5_32.dat','gpfdist://sdw11:21567/catalog_sales_6_32.dat','gpfdist://sdw11:21567/catalog_sales_7_32.dat','gpfdist://sdw11:21567/catalog_sales_8_32.dat','gpfdist://sdw12:21567/catalog_sales_9_32.dat','gpfdist://sdw12:21567/catalog_sales_10_32.dat','gpfdist://sdw12:21567/catalog_sales_11_32.dat','gpfdist://sdw12:21567/catalog_sales_12_32.dat','gpfdist://sdw13:21567/catalog_sales_13_32.dat','gpfdist://sdw13:21567/catalog_sales_14_32.dat','gpfdist://sdw13:21567/catalog_sales_15_32.dat','gpfdist://sdw13:21567/catalog_sales_16_32.dat','gpfdist://sdw14:21567/catalog_sales_17_32.dat','gpfdist://sdw14:21567/catalog_sales_18_32.dat','gpfdist://sdw14:21567/catalog_sales_19_32.dat','gpfdist://sdw14:21567/catalog_sales_20_32.dat','gpfdist://sdw15:21567/catalog_sales_21_32.dat','gpfdist://sdw15:21567/catalog_sales_22_32.dat','gpfdist://sdw15:21567/catalog_sales_23_32.dat','gpfdist://sdw15:21567/catalog_sales_24_32.dat','gpfdist://sdw16:21567/catalog_sales_25_32.dat','gpfdist://sdw16:21567/catalog_sales_26_32.dat','gpfdist://sdw16:21567/catalog_sales_27_32.dat','gpfdist://sdw16:21567/catalog_sales_28_32.dat','gpfdist://sdw9:21567/catalog_sales_29_32.dat','gpfdist://sdw9:21567/catalog_sales_30_32.dat','gpfdist://sdw9:21567/catalog_sales_31_32.dat','gpfdist://sdw9:21567/catalog_sales_32_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

DROP EXTERNAL TABLE IF EXISTS store_sales_ext;
CREATE EXTERNAL TABLE store_sales_ext
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
LOCATION('gpfdist://sdw10:21567/store_sales_4_32.dat','gpfdist://sdw10:21567/store_sales_2_32.dat','gpfdist://sdw10:21567/store_sales_3_32.dat','gpfdist://sdw10:21567/store_sales_1_32.dat','gpfdist://sdw11:21567/store_sales_5_32.dat','gpfdist://sdw11:21567/store_sales_6_32.dat','gpfdist://sdw11:21567/store_sales_8_32.dat','gpfdist://sdw11:21567/store_sales_7_32.dat','gpfdist://sdw12:21567/store_sales_9_32.dat','gpfdist://sdw12:21567/store_sales_11_32.dat','gpfdist://sdw12:21567/store_sales_12_32.dat','gpfdist://sdw12:21567/store_sales_10_32.dat','gpfdist://sdw13:21567/store_sales_15_32.dat','gpfdist://sdw13:21567/store_sales_14_32.dat','gpfdist://sdw13:21567/store_sales_16_32.dat','gpfdist://sdw13:21567/store_sales_13_32.dat','gpfdist://sdw14:21567/store_sales_20_32.dat','gpfdist://sdw14:21567/store_sales_18_32.dat','gpfdist://sdw14:21567/store_sales_19_32.dat','gpfdist://sdw14:21567/store_sales_17_32.dat','gpfdist://sdw15:21567/store_sales_22_32.dat','gpfdist://sdw15:21567/store_sales_23_32.dat','gpfdist://sdw15:21567/store_sales_21_32.dat','gpfdist://sdw15:21567/store_sales_24_32.dat','gpfdist://sdw16:21567/store_sales_28_32.dat','gpfdist://sdw16:21567/store_sales_25_32.dat','gpfdist://sdw16:21567/store_sales_27_32.dat','gpfdist://sdw16:21567/store_sales_26_32.dat','gpfdist://sdw9:21567/store_sales_31_32.dat','gpfdist://sdw9:21567/store_sales_32_32.dat','gpfdist://sdw9:21567/store_sales_29_32.dat','gpfdist://sdw9:21567/store_sales_30_32.dat')
FORMAT 'TEXT' (DELIMITER '|' NULL AS '');

