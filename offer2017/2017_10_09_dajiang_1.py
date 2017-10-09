# -*- coding: UTF-8 -*-
import re

text="x@#T$da+(86)18234859238+A38)sdfMR.X:0755-26656677!26656677!13770625756"
#text=raw_input()

# 先找手机号
mobile_list = re.findall(r"\+\(86\)?1\d{10}",text)
for v in mobile_list:
	print v,","

phone_list = re.findall(r"\(?0\d{2,3}[) -]?\d{7,8}",text)
for v in phone_list:
	print v,","
