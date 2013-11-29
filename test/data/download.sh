#!/bin/sh

FILE_ID="0B3ylb_x4-XOgTnI5UW9sNzdjeTg"
FILE_NAME="pnitools-test-data.tar.gz"
HOST_URL="https://googledrive.com/host/"

wget --no-check-certificate -O$FILE_NAME "$HOST_URL$FILE_ID"

