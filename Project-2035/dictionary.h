struct Word {
   char* letters;
   char unique[5];
   int counts[5];
   char* hint1;
   char* hint2;
} word;  


Word dictionary[30] = {
    {(char*)"frame", {'f', 'r', 'a', 'm', 'e'}, {1,1,1,1,1}, (char*)"activation ___", (char*)""},
    {(char*)"stack", {'s', 't', 'a', 'c', 'k'}, {1,1,1,1,1}, (char*)"push and pop", (char*)""},
    {(char*)"addiu", {'a', 'd', 'i', 'u', '!'}, {1,2,1,1,0}, (char*)"unsigned add", (char*)"(in MIPS)"},
    {(char*)"array", {'a', 'r', 'y', '!', '!'}, {2,2,1,0,0}, (char*)"instantiate", (char*)"with brackets"},
    {(char*)"fault", {'f', 'a', 'u', 'l', 't'}, {1,1,1,1,1}, (char*)"segmentation", (char*)"______"},
    {(char*)"break", {'b', 'r', 'e', 'a', 'k'}, {1,1,1,1,1}, (char*)"exits the", (char*)"loop"},
    {(char*)"debug", {'d', 'e', 'b', 'u', 'g'}, {1,1,1,1,1}, (char*)"remove errors", (char*)"from code"},
    {(char*)"shift", {'s', 'h', 'i', 'f', 't'}, {1,1,1,1,1}, (char*)"bitwise", (char*)"operation"},
    {(char*)"align", {'a', 'l', 'i', 'g', 'n'}, {1,1,1,1,1}, (char*)"data ____ment", (char*)""},
    {(char*)"bytes", {'b', 'y', 't', 'e', 's'}, {1,1,1,1,1}, (char*)"8 bits make", (char*)"these up"},

    {(char*)"coder", {'c', 'o', 'd', 'e', 'r'}, {1,1,1,1,1}, (char*)"person who", (char*)"writes software"},
    {(char*)"logic", {'l', 'o', 'g', 'i', 'c'}, {1,1,1,1,1}, (char*)"______", (char*)"gates"},
    {(char*)"clock", {'c', 'l', 'o', 'k', '!'}, {2,1,1,1,0}, (char*)"______", (char*)"cycle"},
    {(char*)"block", {'b', 'l', 'o', 'c', 'k'}, {1,1,1,1,1}, (char*)"a chunk or", (char*)"portion of code"},
    {(char*)"input", {'i', 'n', 'p', 'u', 't'}, {1,1,1,1,1}, (char*)"'put in' to", (char*)"a function"},
    {(char*)"count", {'c', 'o', 'u', 'n', 't'}, {1,1,1,1,1}, (char*)"keeping track", (char*)"of a loop"},
    {(char*)"trace", {'t', 'r', 'a', 'c', 'e'}, {1,1,1,1,1}, (char*)"look through", (char*)"your code"},
    {(char*)"ascii", {'a', 's', 'c', 'i', '!'}, {1,1,1,2,0}, (char*)"table of", (char*)"character codes"},
    {(char*)"octal", {'o', 'c', 't', 'a', 'l'}, {1,1,1,1,1}, (char*)"base-8", (char*)"number system"},
    {(char*)"crash", {'c', 'r', 'a', 's', 'h'}, {1,1,1,1,1}, (char*)"code stops", (char*)"due to error"},

    {(char*)"pixel", {'p', 'i', 'x', 'e', 'l'}, {1,1,1,1,1}, (char*)"unit element", (char*)"of a picture"},
    {(char*)"queue", {'q', 'u', 'e', 'u', 'e'}, {1,1,1,1,1}, (char*)"FIFO data", (char*)"structure"},
    {(char*)"reset", {'r', 'e', 's', 't', '!'}, {1,2,1,1,0}, (char*)"restore initial", (char*)"conditions"},
    {(char*)"write", {'w', 'r', 'i', 't', 'e'}, {1,1,1,1,1}, (char*)"print code to", (char*)"the terminal"},
    {(char*)"token", {'t', 'o', 'k', 'e', 'n'}, {1,1,1,1,1}, (char*)"the 'words'", (char*)"of code"},
    {(char*)"arrow", {'a', 'r', 'o', 'w', '!'}, {1,2,1,1,0}, (char*)"helps visualise", (char*)"a pointer"},
    {(char*)"field", {'f', 'i', 'e', 'l', 'd'}, {1,1,1,1,1}, (char*)"also called", (char*)"a variable"},
    {(char*)"cache", {'c', 'a', 'h', 'e', '!'}, {2,1,1,1,0}, (char*)"stores data", (char*)""},
    {(char*)"right", {'r', 'i', 'g', 'h', 't'}, {1,1,1,1,1}, (char*)"shift direction", (char*)"to divide"},
    {(char*)"false", {'f', 'a', 'l', 's', 'e'}, {1,1,1,1,1}, (char*)"one value of", (char*)"a boolean"}
};