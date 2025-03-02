#!/bin/bash

echo USERNAME=$USER > .devcontainer/.env
echo GROUPNAME=$(id -gn $USER) >> .devcontainer/.env
echo USER_UID=$(id -u $USER) >> .devcontainer/.env
echo GROUP_GID=$(id -g $USER) >> .devcontainer/.env
echo WORKSPACE=${@} >> .devcontainer/.env
echo PACKAGE_MANAGER=yay >> .devcontainer/.env
