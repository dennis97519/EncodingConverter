# EncodingConverter
[![Github All Releases](https://img.shields.io/github/downloads/dennis97519/EncodingConverter/total.svg)](https://github.com/dennis97519/EncodingConverter/releases)
[![Build status](https://ci.appveyor.com/api/projects/status/ih86toh7q9c59efj?svg=true)](https://ci.appveyor.com/project/dennis97519/encodingconverter)

Convert garbled file name encoding to UTF(16? anyway the encoding used for NTFS)

E.g. after extracting some Japanese app or game's zip you see unreadable text, because the file name are stored as Shift JIS on disk but is interpreted by Windows as some other encoding.

Tested to work on Windows where "Language for Non-Unicode Programs" is set to Chinese (Simplified, China). 

So Windows actually first interpreted the Shift-JIS encoded characters as GB18030, converted it to Unicode and gave it to Qt. The program has to first convert it into GB18030 then interpret it as Shift-JIS and decode into Unicode.

The folder path input box doesn't update the tree view. It only provides input to the file choser after clicking browse.

If you are sure about the actual encoding, try changing the system encoding. The author of the archive may have another default encoding on the system that further garbles things up. I've got a zip with file names that are SJIS reinterpreted as Code Page 850, and probably stored as UTF16.

## Usage
![encconv](https://user-images.githubusercontent.com/4066022/37687106-468dd94c-2c68-11e8-8cc2-4a487c7b3759.PNG)

1. Download the zip
2. (extract and) open EncodingConverter.exe. If missing dll, run the vcredist installer in the zip.
3. Browse to the folder with encoding problems
4. Select the correct encoding
5. Apply

### Features I would like to add:
- [Show root folder somehow](https://forum.qt.io/topic/74756/show-root-path-in-qtreeview-for-qfilesystemmodel/9) in the treeview
- Add [checkboxes](https://stackoverflow.com/questions/26125363/how-to-add-checkbox-on-qtreeview-qfilesystemmodel) to treeview so some files and folders can be skipped 
- Convert encoding of plain text files at the same time (toogle via another checkbox)
