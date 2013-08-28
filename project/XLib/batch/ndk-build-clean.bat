echo off

set batch_dir_full=%~dp0
set batch_dir_full=%batch_dir_full:\=/%
echo on
bash --login -c "cd %batch_dir_full%;./ndk-build-clean.sh"
