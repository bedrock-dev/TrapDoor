if((certutil -hashfile .\bedrock_server.exe md5 | Select-String -Pattern 'f1d88123175ce6dfb602c55f5b8f1be5') -ne $null){echo "正确的版本"}else{echo "错误的版本"}