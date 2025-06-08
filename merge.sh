#!/bin/bash

set -e
set -o pipefail

git fetch origin

# Ensure working tree is clean
if [[ -n $(git status --porcelain) ]]; then
  echo "Error: Working directory is not clean. Commit or stash changes first."
  exit 1
fi

echo "Merging origin/release/v1.0 into release/v1.1..."
git checkout release/v1.1
git merge --no-ff origin/release/v1.0 -m "Merge origin/release/v1.0 into release/v1.1"
git push origin release/v1.1

echo "Merging origin/release/v1.1 into dev..."
git checkout dev
git merge --no-ff origin/release/v1.1 -m "Merge origin/release/v1.1 into dev"
git push origin dev

echo "Merge and push completed successfully."
