Add-Type -AssemblyName System.Windows.Forms
function Open-FileDialog {
        [cmdletBinding()]
        param(
            [Parameter()]
            [ValidateScript({Test-Path $_})]
            [String]
            $InitialDirectory
        )
    Add-Type -AssemblyName System.Windows.Forms
    $FileBrowser = New-Object System.Windows.Forms.OpenFileDialog 
    if($InitialDirectory){
        $FileBrowser.InitialDirectory = $InitialDirectory
    }

    else{
    $fileBrowser.InitialDirectory = [Environment]::GetFolderPath('MyDocuments')
    }
    $FileBrowser.Filter = 'bedrock_server (*.exe)|*.exe|All Files (*.*)|*.*'

[void]$FileBrowser.ShowDialog()
$FileBrowser.FileName
}

$file = Open-FileDialog 
if((certutil -hashfile  $file | Select-String -Pattern 'f0dc8804db447ca287a5f0ba5c5f5a0774a2cdd5') -ne $null)
{
[System.Windows.Forms.MessageBox]::Show("Right Version","OK",[System.Windows.Forms.MessageBoxButtons]::OKCancel,[System.Windows.Forms.MessageBoxIcon]::Asterisk)
}else {
[System.Windows.Forms.MessageBox]::Show("Wrong Version","Error",[System.Windows.Forms.MessageBoxButtons]::OKCancel,[System.Windows.Forms.MessageBoxIcon]::Hand)
}

