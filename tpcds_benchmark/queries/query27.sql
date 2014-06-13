drop table if exists q27;
create table q27 as (
  select
  i_item_id,
  s_state,
  grouping(s_state) g_state, -- Commented out for Impala
    avg(ss_quantity) agg1,
      avg(ss_list_price) agg2,
      avg(ss_coupon_amt) agg3,
      avg(ss_sales_price) agg4
    from
      store_sales_25,
      customer_demographics,
      date_dim,
      store,
      item
    where
      ss_sold_date_sk = d_date_sk
      and ss_item_sk = i_item_sk
      and ss_store_sk = s_store_sk
      and ss_cdemo_sk = cd_demo_sk
      and cd_gender = 'F'
      and cd_marital_status = 'W'
      and cd_education_status = 'Primary'
      and d_year = 1998
      and s_state in ('WI', 'CA', 'TX', 'FL', 'WA', 'TN')
      -- and ss_sold_date_sk between 2450815 and 2451179  -- partition key filter
    group by
      rollup (i_item_id, s_state), -- Commented out for Impala
        i_item_id,
          s_state
        order by
          i_item_id,
          s_state
        limit 100
    );
