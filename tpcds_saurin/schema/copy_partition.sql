SET gp_autostats_mode = 'NONE';

INSERT INTO customer_address SELECT * FROM customer_address_ext;
INSERT INTO customer_demographics SELECT * FROM customer_demographics_ext;
INSERT INTO date_dim SELECT * FROM date_dim_ext;
INSERT INTO warehouse SELECT * FROM warehouse_ext;
INSERT INTO ship_mode SELECT * FROM ship_mode_ext;
INSERT INTO time_dim SELECT * FROM time_dim_ext;
INSERT INTO reason SELECT * FROM reason_ext;
INSERT INTO income_band SELECT * FROM income_band_ext;
INSERT INTO item SELECT * FROM item_ext;
INSERT INTO store SELECT * FROM store_ext;
INSERT INTO call_center SELECT * FROM call_center_ext;
INSERT INTO customer SELECT * FROM customer_ext;
INSERT INTO web_site SELECT * FROM web_site_ext;
INSERT INTO store_returns SELECT * FROM store_returns_ext;
INSERT INTO household_demographics SELECT * FROM household_demographics_ext;
INSERT INTO web_page SELECT * FROM web_page_ext;
INSERT INTO promotion SELECT * FROM promotion_ext;
INSERT INTO catalog_page SELECT * FROM catalog_page_ext;
INSERT INTO inventory SELECT * FROM inventory_ext;
INSERT INTO catalog_returns SELECT * FROM catalog_returns_ext;
INSERT INTO web_returns SELECT * FROM web_returns_ext;
INSERT INTO web_sales SELECT * FROM web_sales_ext;
INSERT INTO catalog_sales SELECT * FROM catalog_sales_ext;
INSERT INTO store_sales SELECT * FROM store_sales_ext;




ALTER TABLE customer_address ADD primary key (ca_address_sk);
ALTER TABLE customer_demographics ADD primary key (cd_demo_sk);
ALTER TABLE date_dim ADD primary key (d_date_sk, d_year);
ALTER TABLE warehouse ADD primary key (w_warehouse_sk);
ALTER TABLE ship_mode ADD primary key (sm_ship_mode_sk);
ALTER TABLE time_dim ADD primary key (t_time_sk);
ALTER TABLE reason ADD primary key (r_reason_sk);
ALTER TABLE income_band ADD primary key (ib_income_band_sk);
ALTER TABLE item ADD primary key (i_item_sk);
ALTER TABLE store ADD primary key (s_store_sk);
ALTER TABLE call_center ADD primary key (cc_call_center_sk);
ALTER TABLE customer ADD primary key (c_customer_sk);
ALTER TABLE web_site ADD primary key (web_site_sk);
ALTER TABLE store_returns ADD primary key (sr_item_sk, sr_ticket_number, sr_returned_date_sk);
ALTER TABLE household_demographics ADD primary key (hd_demo_sk);
ALTER TABLE web_page ADD primary key (wp_web_page_sk);
ALTER TABLE promotion ADD primary key (p_promo_sk);
ALTER TABLE catalog_page ADD primary key (cp_catalog_page_sk);
ALTER TABLE inventory ADD primary key (inv_date_sk, inv_item_sk, inv_warehouse_sk);
ALTER TABLE catalog_returns ADD primary key (cr_item_sk, cr_order_number, cr_returned_date_sk);
ALTER TABLE web_returns ADD primary key (wr_item_sk, wr_order_number, wr_returned_date_sk);
ALTER TABLE web_sales ADD primary key (ws_item_sk, ws_order_number, ws_sold_date_sk);
ALTER TABLE catalog_sales ADD primary key (cs_item_sk, cs_order_number, cs_sold_date_sk);
ALTER TABLE store_sales ADD primary key (ss_item_sk, ss_ticket_number, ss_sold_date_sk);






--DROP EXTERNAL TABLE IF EXISTS customer_address_ext;
--DROP EXTERNAL TABLE IF EXISTS customer_demographics_ext;
--DROP EXTERNAL TABLE IF EXISTS date_dim_ext;
--DROP EXTERNAL TABLE IF EXISTS warehouse_ext;
--DROP EXTERNAL TABLE IF EXISTS ship_mode_ext;
--DROP EXTERNAL TABLE IF EXISTS time_dim_ext;
--DROP EXTERNAL TABLE IF EXISTS reason_ext;
--DROP EXTERNAL TABLE IF EXISTS income_band_ext;
--DROP EXTERNAL TABLE IF EXISTS item_ext;
--DROP EXTERNAL TABLE IF EXISTS store_ext;
--DROP EXTERNAL TABLE IF EXISTS call_center_ext;
--DROP EXTERNAL TABLE IF EXISTS customer_ext;
--DROP EXTERNAL TABLE IF EXISTS web_site_ext;
--DROP EXTERNAL TABLE IF EXISTS store_returns_ext;
--DROP EXTERNAL TABLE IF EXISTS household_demographics_ext;
--DROP EXTERNAL TABLE IF EXISTS web_page_ext;
--DROP EXTERNAL TABLE IF EXISTS promotion_ext;
--DROP EXTERNAL TABLE IF EXISTS catalog_page_ext;
--DROP EXTERNAL TABLE IF EXISTS inventory_ext;
--DROP EXTERNAL TABLE IF EXISTS catalog_returns_ext;
--DROP EXTERNAL TABLE IF EXISTS web_returns_ext;
--DROP EXTERNAL TABLE IF EXISTS web_sales_ext;
--DROP EXTERNAL TABLE IF EXISTS catalog_sales_ext;
--DROP EXTERNAL TABLE IF EXISTS store_sales_ext;

ANALYZE;
