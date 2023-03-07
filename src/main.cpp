#include "utils.h"

bool isAlpha(char ch) {
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')); 
}

bool isOption(string opt) {
    set<string> opts = {"-n", "-w", "-c", "-r"};
    return (opts.count(opt) != 0);
}

bool isOptionWithValue(string opt) {
    set<string> opts = {"-h", "-t", "-j"};
    return (opts.count(opt) != 0);
}

bool isDuplicate(map<char, char>& opt2val, string& arg) {
    return (opt2val.count(arg.at(1)) == 1);
}

void lexerOption(queue<string>& args, map<char, char>& opt2val) {
    if (isDuplicate(opt2val, args.front())) {
        throw exception();
    } else {
        opt2val[args.front().at(1)] = 0;
        args.pop();
    }
}

void lexerOptionWithValue(queue<string>& args, map<char, char>& opt2val) {
    string opt = args.front();
    args.pop();
    // test
    if (args.empty()) {
        throw exception();
    } else {
        if (args.front().size() == 1 && isAlpha(args.front().at(0))) {
            if (isDuplicate(opt2val, opt)) {
                throw exception();
            } else {
                opt2val[opt.at(1)] = args.front().at(0);
                args.pop();
            }
        } else {
            throw exception();  // 带值选项带非法参数
        } 
    }
}

void lexerFileName(queue<string>& args, string& fileName) {
    if (args.front().at(0) == '-') {
        throw exception();  // 非法选项
    }
    if (fileName.size() == 0) {
        fileName = args.front();
        args.pop();
    } else {
        throw exception(); 
    }
}

void lexerArgs(int argc, char* argv[], map<char, char>& opt2val, string& fileName) {
    queue<string> args; 
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        args.push(arg);
    }

    while (!args.empty()) {
        if (isOption(args.front())) {
            lexerOption(args, opt2val);
        } else if (isOptionWithValue(args.front())) {
            lexerOptionWithValue(args, opt2val);
        } else {
            lexerFileName(args, fileName);
        }
    } 
}

void isLegalOpt(map<char, char>& opt2val) {
    if (opt2val.count('n') + opt2val.count('w') + opt2val.count('c') < 1) {
        throw exception(); //缺少功能型参数
    } else if (opt2val.count('n') + opt2val.count('w') + opt2val.count('c') > 1) {
        throw exception(); //功能型参数重复
    }
}

int readWords(string fileName, char** words) {
    ifstream readFile(fileName);

    if (readFile.fail()) {
        cout << "fileName is illegal" << endl;
        throw exception(); //打开文件失败
    }

    string data;
    int cnt = 0;
    vector<char> wordBuf;

    while (getline(readFile, data)) {
        data += "\n";
        for (int i = 0; i < data.size(); i++) {
            if (isAlpha(data.at(i))) {
                wordBuf.push_back(data.at(i));
            } else {
                if (wordBuf.size() > 0) {
                    wordBuf.push_back('\0');
                    words[cnt] = (char *) malloc(sizeof(char) * wordBuf.size());
                    for (int j = 0; j < wordBuf.size(); j++) {
                        words[cnt][j] = wordBuf[j];
                    }
                    wordBuf.clear();
                    cnt++;
                }
            }
        }
    }

    return cnt;
}


int main(int argc, char* argv[]) {
    map<char, char> opt2val;
    string fileName;
    lexerArgs(argc, argv, opt2val, fileName);

    isLegalOpt(opt2val);

    char **words = (char **) malloc(sizeof(char *) * MAX_WORDS_NUM);
    char **result = (char**) malloc (sizeof (char*) * MAX_CHAINS_NUM);
    int length = readWords(fileName, words);

    char head = (opt2val.count('h') > 0) ? opt2val['h'] : '\0';
    char tail = (opt2val.count('t') > 0) ? opt2val['t'] : '\0';
    char ban = (opt2val.count('j') > 0) ? opt2val['j'] : '\0'; 
    bool allow_circle = (opt2val.count('r'));

    int ret;

    try {
        if (opt2val.count('n') > 0) {
            ret = countChains(words, length, result);
        } else if (opt2val.count('w') > 0) {
            ret = getLongestWordChain(words, length, result, head, tail, ban, allow_circle);
        } else if (opt2val.count('c') > 0) {
            ret = getLongestCharChain(words, length, result, head, tail, ban, allow_circle);
        }
    } catch (exception& e) {
        string err = e.what();
        cout << "error: " + err << endl; 
    }

    return 0;
}