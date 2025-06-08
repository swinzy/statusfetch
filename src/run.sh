#!/bin/bash

# Load .env
if [ -f .env ]; then
  set -a
  source .env
  set +a
else
  echo "No .env file. Please create .env file and put GITHUB_TOKEN=... Make sure you have the least permission for security purpose."
  exit 1
fi

# Point to executable
./statusfetch

