chcp 65001
$INJECTOR = "MCDllInject.exe"
$GAME_VERSION = "1.16.210.06"
$BDS_DIR = "C:\Users\xhy\Desktop\MC\bedrock-server-" + $GAME_VERSION + "\"
$TD_BUILD_DIR = "C:\Users\xhy\dev\TrapDoor\cmake-build-release\"
$BDS_FILE = $BDS_DIR + "bedrock_server.exe"
$LOG_DIR = "C:\Users\xhy\dev\TrapDoor\log\"
$Date = $( get-date -f yyyy-MM-dd ) + " " + $( get-date -f HH-mm-ss )

Write-Output "ues injector          "$INJECTOR
Write-Output "game version is       "$GAME_VERSION
Write-Output "bds location is       "$BDS_FILE
Write-Output "trapdoor build dir is "$TD_BUILD_DIR

Set-Location $BDS_DIR
Invoke-Expression $INJECTOR" "$BDS_FILE" "$TD_BUILD_DIR | Tee-Object $LOG_DIR""$Date".txt"
