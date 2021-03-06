drop table if exists q55;
create table q55 as (
select
  i_brand_id brand_id,
  i_brand brand,
  sum(ss_ext_sales_price) ext_price
from
  date_dim,
  store_sales_25,
  item
where
  d_date_sk = ss_sold_date_sk
  and ss_item_sk = i_item_sk
  and i_manager_id = 36
  and d_moy = 12
  and d_year = 2001
  -- and ss_sold_date_sk between 2452245 and 2452275 -- partition key filter
group by
  i_brand,
  i_brand_id
order by
  ext_price desc,
  i_brand_id
limit 100 
);
