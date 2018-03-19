# EncodingConverter
Convert garbled file name encoding to UTF(16? anyway the encoding used for NTFS)

E.g. after extracting some Japanese app or game's zip you see unreadable text, because the file name are stored as Shift JIS on disk but is interpreted by Windows as some other encoding.

Tested to work on Windows where "Language for Non-Unicode Programs" is set to Chinese (Simplified, China). 

So Windows actually first interpreted the Shift-JIS encoded characters as GB18030, converted it to Unicode and gave it to Qt. The program has to first convert it into GB18030 then interpret it as Shift-JIS and decode into Unicode.

The folder path input box doesn't update the tree view. It only provides input to the file choser after clicking browse.
