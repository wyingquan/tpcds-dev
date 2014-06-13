--set statement_mem=3670016;
drop table if exists q42;
create table q42 as (
select
  dt.d_year,
  item.i_category_id,
  item.i_category,
  sum(ss_ext_sales_price)
from
  date_dim dt,
  store_sales_25,
  item
where
  dt.d_date_sk = store_sales_25.ss_sold_date_sk
  and store_sales_25.ss_item_sk = item.i_item_sk
  and item.i_manager_id = 1
  and dt.d_moy = 12
  and dt.d_year = 1998
  -- and ss_sold_date_sk between 2451149 and 2451179  -- partition key filter
group by
  dt.d_year,
  item.i_category_id,
  item.i_category
order by
  sum(ss_ext_sales_price) desc,
  dt.d_year,
  item.i_category_id,
  item.i_category
limit 100
);
