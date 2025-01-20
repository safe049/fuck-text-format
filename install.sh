echo "Fuck Text Format Installation Program"

echo "Copying files into /usr/bin"

cp fEditorEncoder /usr/bin
cp fEditorDecoder /usr/bin
cp fuckdecoder /usr/bin
cp fuckencoder /usr/bin

echo "Installing vim fEditor fuck editor plugin"
cp fEditor.vim /usr/share/vim/vimfiles/plugin

echo "Installation completed"
echo "fEditor Usage: --------------------------------"
cat fEditorUsage.md
echo "readme: ---------------------------------"
cat README.md