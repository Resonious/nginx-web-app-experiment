#!/bin/bash

docker run --name nginx-webapp-db \
  $@ \
  -e MYSQL_ROOT_PASSWORD=abc123test1847test \
  mysql:latest \
  --character-set-server=utf8mb4 \
  --collation-server=utf8mb4_unicode_ci
