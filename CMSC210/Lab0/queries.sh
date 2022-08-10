#!/bin/bash

curl "https://freesound.org/apiv2/search/text/?query=Boccherini&token=SpBHFwqG5WsY1osEqxXSB6Hofr1zJOC1qi2Dlh7J" | json_pp | grep "id"
