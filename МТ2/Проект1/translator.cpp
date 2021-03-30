#include "translator.h"

// Конструктор со вводом постоянных таблиц
translator::translator(){
    letters.read_file("letters.txt");
    numbers.read_file("numbers.txt");
    operations.read_file("operations.txt");
    keywords.read_file("keywords.txt");
    separators.read_file("separators.txt");
}

// Лексический анализ
bool translator::analyze_lexical(string source, string tokens, string error){
    in.open(source.c_str(), std::fstream::in);
    out.open(tokens.c_str(), std::fstream::out);
    outerror.open(error.c_str(), std::fstream::out);
    bool flag_error = false;
    bool flag_coment = false;
    string str;
    analyze_lexical_strnum = 1;
    while(!in.eof() && !flag_error){
        getline(in, str);
        if(!in.eof()){
            analyze_lexical_strinc = 0;
            string strold = str;
            if(!analyze_lexical_decomment(str, true)){
                outerror << "Error in string " << analyze_lexical_strnum << ": " << strold << endl;
                cout << "Error in string " << analyze_lexical_strnum << ": " << strold << endl;
                return false;
            }
            analyze_lexical_strnum += analyze_lexical_strinc;
            flag_error = !analyze_lexical_string(str);
            if(flag_error){
                outerror << "Error in string " << analyze_lexical_strnum << ": " << str << endl;
                cout << "Error in string " << analyze_lexical_strnum << ": " << str << endl;
            }
            analyze_lexical_strnum ++;
        }
    }
    in.close();
    out.close();
    outerror.close();
    return !flag_error;
}

// Очистка от комментариев
bool translator::analyze_lexical_decomment(string& str, bool is_changed){
   
        bool change = false;
        size_t index_c = str.find("//"), index_c1 = str.find("/*"), index_c2;     /*  //  */
        if (index_c != string::npos && index_c < index_c1){                       //   пример для чего это -   //comment/*  
            str.erase(index_c);
            change = true;
        }
        index_c1 = str.find("/*");
        index_c2 = str.find("*/");
        if(index_c2 < index_c1){
            outerror << "Error: incorrect coment" << endl;
            cout << "Error: incorrect coment" << endl;
            return false;
        }
        while(index_c1 != string::npos && index_c2 != string::npos){ //вырезаем комментарий
            string temp = str;
            str.erase(index_c1);
            temp.erase(0, index_c2 + 2);
            str += temp;
            index_c1 = str.find("/*");
            index_c2 = str.find("*/");
            change = true;
        }

        // если закрытие комментария на другой строке
        // смотрим на других строках
        if(index_c1 != string::npos && index_c2 == string::npos){
            str.erase(index_c1);
            string temp;
            if(!in.eof()){
                getline(in, temp);
                analyze_lexical_strinc++;
            }
            else{
                outerror << "Error: incorrect coment" << endl;
                cout << "Error: incorrect coment" << endl;
                return false;
            }
            while(temp.find("*/") == string::npos){
                if(!in.eof()){
                    getline(in, temp);
                    analyze_lexical_strinc++;
                }
                else{
                    outerror << "Error: incorrect coment" << endl;
                    cout << "Error: incorrect coment" << endl;
                    return false;
                }
            }
            index_c2 = temp.find("*/");
            temp.erase(0, index_c2 + 2);
            str += " " + temp;
            change = true;
        }
        index_c1 = str.find("/*");
        index_c2 = str.find("*/");

        // если есть только закрывающий комменьт
        if(index_c1 == string::npos && index_c2 != string::npos){
            outerror << "Error: incorrect coment" << endl;
            cout << "Error: incorrect coment" << endl;
            return false;
        } 
        if(is_changed)
            return analyze_lexical_decomment(str, change);

    return true;
}

// Анализ строки
bool translator::analyze_lexical_string(string str) {
    space(str);
    bool flag_error = false;
    if (str.size()) {
        cout << "Analyze lexical string started : " << str << endl;
        char symbol_1 = str[0], symbol_2 = str[1];
        // Проверка первого символа
        string str_1, str_2;
        stringstream str_stream;
        str_stream << symbol_1;
        str_1 = str_stream.str();
        str_stream << symbol_2;
        str_2 = str_stream.str();
        int first_sym_type = -1;
        if (letters.check(symbol_1))
            first_sym_type = 0;
        if (numbers.check(symbol_1))
            first_sym_type = 1;
        if (operations.check(str_1) || operations.check(str_2))
            first_sym_type = 2;
        if (separators.check(symbol_1))
            first_sym_type = 3;

        switch (first_sym_type) {
            case -1: {   // Недопустимый символ
                outerror << "Error: unresolved first symbol" << endl;
                cout << "Error: unresolved first symbol" << endl;
                return false;
            }
            break;
        case 0: { // Идентификатор
            // Получим полное название идентификатора
            string idname = str;
            int i;
            bool finded = false;
            for (i = 1; i < idname.size() && !finded; i++)
                finded = !(letters.check(str[i]) || numbers.check(str[i]));
            if (finded) {
                idname.erase(i - 1);
                str.erase(0, i - 1);
            }
            else
                str.erase(0);
            if (keywords.check(idname)) {  // Если ключевое слово
                if (keywords.get_num(idname, i))
                    out << token(3, i, -1);
            }
            else { // Иначе в таблицу идентификаторов
                identificators.add(idname);
                int table, chain;
                identificators.get_location(idname, table, chain);
                out << token(5, table, chain);
            }
            return analyze_lexical_string(str);
        }
              break;
        case 1: {   // Константа
            string constval = str;
            int i;
            bool finded = false;
            for (i = 1; i < constval.size() && !finded; i++)
                finded = !(numbers.check(str[i]) || str[i] == '.');
            string str_t1, str_t2;
            stringstream str_stream_t;
            str_stream_t << str[i - 1];
            str_t1 = str_stream_t.str();
            str_stream_t << str[i];
            str_t2 = str_stream_t.str();
            if (!operations.check(str_t1) && !operations.check(str_t2) && !separators.check(str[i - 1])) {
                outerror << "Error: incorrect constant" << endl;
                cout << "Error: incorrect constant" << endl;
                return false;
            }
            if (finded) {
                constval.erase(i - 1);
                str.erase(0, i - 1);
            }
            else
                str.erase(0);
            if (constval.find_last_of('.') - constval.find_first_of('.') != 0) { // во избежание  конст = 1.1.1
                outerror << "Error: incorrect constant" << endl;
                cout << "Error: incorrect constant" << endl;
                return false;
            }
            else {
                constants.add(constval);
                int table, chain;
                identificators.get_location(constval, table, chain);
                out << token(6, table, chain);
            }
            return analyze_lexical_string(str);
        }
              break;
        case 2: { // Операция
            int table;
            if (operations.check(str_2)) {  // Двухсимвольная
                operations.get_num(str_2, table);
                out << token(4, table, -1);
                str.erase(0, 2);
                return analyze_lexical_string(str);
            }
            if (operations.check(str_1)) {   // Односимвольная
                operations.get_num(str_1, table);
                out << token(4, table, -1);
                str.erase(0, 1);
                return analyze_lexical_string(str);
            }
        }
              break;
        case 3: {  // Разделитель
            int table;
            separators.get_num((const char)str[0], table);
            out << token(4, table, -1);
            str.erase(0, 1);
            return analyze_lexical_string(str);
        }
              break;
        default: {
            outerror << "Error: can`t determine symbol \"" << str_1 << "\"" << endl;
            cout << "Error: can`t determine symbol \"" << str_1 << "\"" << endl;
            return false;
        }
               break;
        }
    }
    return !flag_error;
}