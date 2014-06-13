 -- $Id: ansi.tpl,v 1.3 2006/08/28 18:09:17 jms Exp $
define __LIMITA = "";
define __LIMITB = "top %d";
define __LIMITC = "";
define _BEGIN = "-- start query " + [_QUERY] + " in stream " + [_STREAM] + " using template " + [_TEMPLATE];
define _END = "-- end query " + [_QUERY] + " in stream " + [_STREAM] + " using template " + [_TEMPLATE];
