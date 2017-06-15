#!/bin/sh

FILE_ID="0B3ylb_x4-XOgUkdQSUFQRUhsN0E"
FILE_NAME="pnitools-test-data.tar.gz"
HOST_URL="https://drive.google.com/drive/folders/"

wget --no-check-certificate -O$FILE_NAME "$HOST_URL$FILE_ID"
