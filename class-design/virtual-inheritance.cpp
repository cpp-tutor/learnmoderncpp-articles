class FileBase {
    // Hierarchy base class
};
 
class InputFile : virtual public FileBase {
   // Functionalilty for reading files
};
 
class OutputFile : virtual public FileBase {
    // Functionality for writing files
};
 
class IOFile : public InputFile, public OutputFile {
    // All functionality of both InputFile and OutputFile
    // with one copy of FileBase's members
};
