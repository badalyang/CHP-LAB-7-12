@echo off
:menu
cls
echo ===================================
echo       Windows Utility Menu
echo ===================================
echo 1. Display IP Addresses (IPv4 and IPv6)
echo 2. Perform Traceroute
echo 3. Resolve DNS Name
echo 4. Encrypt Text (Caesar Cipher)
echo 5. Decrypt Text (Caesar Cipher)
echo 6. Encrypt File
echo 7. Decrypt File
echo 8. Compress File (ZIP)
echo 9. Decompress File (ZIP)
echo 10. Calculate Hash for File
echo 0. Exit
echo ===================================
set /p choice="Select an option: "

if "%choice%"=="1" goto get_ip
if "%choice%"=="2" goto traceroute
if "%choice%"=="3" goto resolve_dns
if "%choice%"=="4" goto encrypt_text
if "%choice%"=="5" goto decrypt_text
if "%choice%"=="6" goto encrypt_file
if "%choice%"=="7" goto decrypt_file
if "%choice%"=="8" goto compress_file
if "%choice%"=="9" goto decompress_file
if "%choice%"=="10" goto hash_value
if "%choice%"=="0" goto exit
goto menu

:get_ip
cls
echo Displaying IP Addresses...
ipconfig | findstr "IPv4"
ipconfig | findstr "IPv6"
pause
goto menu

:traceroute
cls
set /p target="Enter the hostname or IP address: "
echo Performing traceroute to %target%...
tracert %target%
pause
goto menu

:resolve_dns
cls
set /p dns_name="Enter the DNS name: "
echo Resolving DNS name...
nslookup %dns_name%
pause
goto menu

:encrypt_text
cls
set /p text="Enter text to encrypt: "
set /p shift="Enter shift value for Caesar Cipher: "
call :caesar_encrypt "%text%" %shift%
pause
goto menu

:decrypt_text
cls
set /p text="Enter text to decrypt: "
set /p shift="Enter shift value for Caesar Cipher: "
set /a shift=0-%shift%
call :caesar_encrypt "%text%" %shift%
pause
goto menu

:encrypt_file
cls
set /p file="Enter the file path to encrypt: "
echo Encrypting file %file%...
echo Sorry, this functionality requires external scripts.
pause
goto menu

:decrypt_file
cls
set /p file="Enter the file path to decrypt: "
echo Decrypting file %file%...
echo Sorry, this functionality requires external scripts.
pause
goto menu

:compress_file
cls
set /p file="Enter the file path to compress: "
set /p zipname="Enter the name for the zip file: "
echo Compressing %file% to %zipname%.zip...
powershell Compress-Archive -Path "%file%" -DestinationPath "%zipname%.zip"
pause
goto menu

:decompress_file
cls
set /p zipfile="Enter the path to the ZIP file: "
set /p extractpath="Enter the extraction path: "
echo Decompressing %zipfile% to %extractpath%...
powershell Expand-Archive -Path "%zipfile%" -DestinationPath "%extractpath%"
pause
goto menu

:hash_value
cls
echo ===================================
echo     Calculate Hash Value
echo ===================================
echo 1. Calculate Hash for Text
echo 2. Calculate Hash for File
echo 0. Back to Main Menu
echo ===================================
set /p hash_choice="Select an option: "

if "%hash_choice%"=="1" goto hash_text
if "%hash_choice%"=="2" goto hash_file
if "%hash_choice%"=="0" goto menu
goto hash_value

:hash_text
cls
set /p text="Enter the text to calculate hash: "
:: Save the text to a temporary file
echo %text% > temp_text.txt
:: Calculate hash values
echo ===================================
echo Calculating MD5 Hash...
certutil -hashfile temp_text.txt MD5
echo Calculating SHA256 Hash...
certutil -hashfile temp_text.txt SHA256
:: Clean up temporary file
del temp_text.txt
echo ===================================
pause
goto hash_value

:hash_file
cls
set /p file_path="Enter the file path to calculate hash: "
if not exist "%file_path%" (
    echo File does not exist. Please try again.
    pause
    goto hash_value
)
:: Calculate hash values
echo ===================================
echo Calculating MD5 Hash...
certutil -hashfile "%file_path%" MD5
echo Calculating SHA256 Hash...
certutil -hashfile "%file_path%" SHA256
echo ===================================
pause
goto hash_value

:exit
echo Exiting... Goodbye!
exit

:caesar_encrypt
:: Function to perform Caesar Cipher encryption/decryption
setlocal enabledelayedexpansion
set input=%1
set shift=%2
set output=
for /l %%i in (0,1,127) do (
    set "char=%%i"
    set /a "new_char=char+shift"
    if !new_char! gtr 127 set /a new_char-=128
    if !new_char! lss 0 set /a new_char+=128
    set output=!output!!new_char!
)
echo Encrypted/Decrypted Text: !output!
endlocal
goto :eof
