# Clears out the build directories.
# We are chucking the error stream to null in case we clean an already clean directory.
Write-Output "Clean out build directories & files..."
$StartingTime = Get-Date

rm -Force -Recurse .\build 2> $null
rm -Force -Recurse .\bin 2> $null
rm -Force -Recurse .\.vs 2> $null
rm -Force -Recurse .\CMakeFiles 2> $null

rm -Force .\CMakeCache.txt 2> $null
rm -Force .\cmake_install.cmake 2> $null
rm -Force .\*.vcxproj* 2> $null
rm -Force .\*.sln 2> $null

$EndingTime = Get-Date
$Finish = New-Timespan -Start $StartingTime -End $EndingTime
Write-Output "Clean completed in $Finish."