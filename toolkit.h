//usefull pack:{
#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <iostream>// for printing
#include <cmath>// for std::abs
// #include <cstdlib> // for rand(), srand(), RAND_MAX
#include <climits> // for UINT_MAX
#include <chrono>//for the delay function
#include <thread>//for the delay function
// #include <algorithm> // For std::min
#include <fstream> // For file manipulationsmanipulations
#include <atomic>  // for AtomicLock class


#define SUPPORTS_PRETTY_FUNC defined(__GNUC__) || defined(__clang__) || defined(__INTEL_COMPILER)



//function end
struct FND {};

//macros {
#if true
    //mini macro functions
    #define IS_CONTINUATION_CHAR(c)     (0xC2  <= c && c <= 0xF4)
    #define IS_MULTI_BYTE_CHAR_START(c) (0x80 <= c && c <= 0xBF)
    #define IS_VALID(x)                 (x == x && x != INFINITY && x != -INFINITY)
    #define ABS(x)                      ((x < 0)?(-x):(x))
    #define LOWERCASE(x)                (('A' <= x && x <= 'Z')?('a' - 'A' + x):(x))
    #define UPPERCASE(x)                (('a' <= x && x <= 'z')?('A' - 'a' + x):(x))
    #define ISLETTER(x)                 (('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z'))
    #define ISLOWERCASELETTER(x)        ('a' <= x && x <= 'z')
    #define ISUPPERCASELETTER(x)        ('A' <= x && x <= 'Z')
    #define ISNUMBER(x)                 ('0' <= x && x <= '9')
    #define MIN(a, b)                   ((a<b)?(a):(b))
    #define MAX(a, b)                   ((a>b)?(a):(b))
    #define IS_UNSIGNED(x)              (x >= 0 && ~x >= 0)
    #define FLOOR(x)                    ((x) >= 0 ? (long long)(x) : ((x) == (long long)(x) ? (long long)(x) : (long long)(x) - 1))
    #define CEIL(x)                     ((x) <= 0 ? (long long)(x) : ((x) == (long long)(x) ? (long long)(x) : (long long)(x) + 1))
    #define MOD(a, b)                   (((a) % (b) + (b)) % (b))
    #define GRID_SIZE(w, h)             (CEIL((double)((w) * (h)) / 8.0))
    #define PADD PADL
    #define PADL(padd_c, ...)           std::string(MAX(0, padd_c - getLen(__VA_ARGS__)), ' '), __VA_ARGS__
    #define PADR(padd_c, ...)           __VA_ARGS__, std::string(MAX(0, padd_c - getLen(__VA_ARGS__)), ' ')


    //line tracking stuff
    #define LINE_TRACKER                FND = FND(), int line = __builtin_LINE(), const char* file = __builtin_FILE()
    #define LINE_TRACKER_SHELL          FND, int line, const char* file
    #define LINE_TRACKER_INPUT          FND(), line, file
    #define ERROR_LINE                  "ERROR line ",line," in file ",file,", "
    #define ERROR_LINE_PRIMITIVE         "ERROR line ",__LINE__," in file ",__FILE__,", "

    //constants
    #define INLINE [[__gnu__::__always_inline__]]
    #define IOSTREAM defined(_GLIBCXX_IOSTREAM) || defined(_LIBCPP_IOSTREAM) || defined(_IOSTREAM_) 
    
    #define LINE_DEBUG println("LINE : ",__LINE__);
    #define DEBUG(...)(debugHelper(0, #__VA_ARGS__, __VA_ARGS__))
    #define BIN_DEBUG(x) print(#x); print(" = "); printlnbin(x)
    #define HEX_DEBUG(x) print(#x); print(" = "); printlnhex(x)
    #define DEBUG_BANNER debug_banner_h
    #define DEBUG_BOUND debug_bound_h
    #define UINT_MIN 0
    #define sizeofarray(x) (sizeof(x)/sizeof(x[0]))
    #define sofa sizeofarray
    #define printerror(...) (println("ERROR in file ",__FILE__," in function ",__func__," at line ",__LINE__,", ",__VA_ARGS__))
    #define clearArray(arr, ...) \
    for(int __pAgD67o5 = 0; __pAgD67o5 < sizeofarray(arr); __pAgD67o5++)\
    {\
        arr[__pAgD67o5] = __VA_ARGS__;\
    }
    /**
     * @brief macro that copies arr1 to arr2
     * @param arr1 the array that is getting copied from
     * @param arr2 the destination, where `arr1` is getting copied to
     * @note this macro always chooses the size of the smallest array to copy
     */
    #define copyArray(arr1, arr2) \
    for(int __pAgD67o5 = 0; __pAgD67o5 < MIN(sizeofarray(arr1), sizeofarray(arr2)); __pAgD67o5++)\
    {\
        arr2[__pAgD67o5] = arr1[__pAgD67o5];\
    }
    #define copyString(source, dest) \
    for(int __pAgD67o5 = 0; __pAgD67o5 < MIN(strlen_tk(source) + 1, strlen_tk(dest) + 1); __pAgD67o5++) \
    { \
        dest[__pAgD67o5] = source[__pAgD67o5]; \
    } \
    dest[MIN(strlen_tk(source), strlen_tk(dest))] = '\0';
    #define printarray(x) printarray_h(x, sizeof(x) / sizeof(x[0]))

#endif //}

//enable_if-like {
#if true
    struct false_t {
        const static bool value = false;
    };

    struct true_t {
        const static bool value = true;
    };
    
    template<typename T>
    struct type_t {
        typedef T type;
    };

    //create a standart struct where you create two types
    template<typename A, typename B> struct is_same       : false_t {};
    template<typename A>             struct is_same<A, A> : true_t  {};

    //create a weird template where Condition is a boolean (boolean not a type), and where you are telling c++ that Type is not a valid type
    template<bool Condition, typename Type = void> struct enable_if             {};
    template<typename Type>                        struct enable_if<true, Type> {typedef Type type;};

    template<bool Condition, typename A, typename B> struct choose_type             {typedef A type;};//when false type = A
    template<typename A, typename B>                 struct choose_type<true, A, B> {typedef B type;};//when true  type = B

    
    //create a check to know if a type is a number or not
    template<typename T>
    struct is_number : false_t {};

    //specialize template for all numbers set value to true
    template<> struct is_number<unsigned char     > : true_t {};
    template<> struct is_number<unsigned short    > : true_t {};
    template<> struct is_number<unsigned int      > : true_t {};
    template<> struct is_number<unsigned long     > : true_t {};
    template<> struct is_number<unsigned long long> : true_t {};
    template<> struct is_number<char              > : true_t {};
    template<> struct is_number<short             > : true_t {};
    template<> struct is_number<int               > : true_t {};
    template<> struct is_number<long              > : true_t {};
    template<> struct is_number<long long         > : true_t {};


    //create a check to know if a type is a pointer
    template<typename T>
    struct is_pointer {
        static const bool value = false;
    };

    //when the template typename can be a type + pointer means we have a pointer so set value to true
    template<typename T>
    struct is_pointer<T*> {
        static const bool value = true;
    };


     //create a check to know if a type is a pointer
    template<typename T>
    struct is_fn {
        static const bool value = false;
    };

    //when the template typename can be a type + pointer means we have a pointer so set value to true
    template<typename Return, typename... Args>
    struct is_fn<Return(Args...)> {
        static const bool value = true;
    };

    
    template<typename T>
    struct remove_references {
        typedef T type;
    };

    //specify but with references
    template<typename T>
    struct remove_references<T&> {
        typedef T type;
    };

    template<typename T> 
    struct remove_pointers {
        typedef T type;
    };

    template<typename T>
    struct remove_pointers<T*> {
        typedef T type;
    };

    template<typename T> class SimPtr;

    template<typename T>
    struct remove_pointers<SimPtr<T>> {
        typedef T type;
    };

    
    template<typename T> struct raw_type                   {typedef T type;};//default, if there is no type modifier, it'll end up here
    template<typename T> struct raw_type<const T>          {typedef typename raw_type<T>::type type;};
    template<typename T> struct raw_type<volatile T>       {typedef typename raw_type<T>::type type;};
    template<typename T> struct raw_type<const volatile T> {typedef typename raw_type<T>::type type;};
    template<typename T> struct raw_type<T&>               {typedef typename raw_type<T>::type type;};
    template<typename T> struct raw_type<T&&>              {typedef typename raw_type<T>::type type;};
    template<typename T> struct raw_type<T*>               {typedef typename raw_type<T>::type type;};

    //default is_unsigned (when not unsigned)
    template<typename T> 
    struct is_unsigned : false_t {};

    //specification where we check all possible unsigned combinations
    template<> struct is_unsigned<unsigned char     > : true_t {};
    template<> struct is_unsigned<unsigned short    > : true_t {};
    template<> struct is_unsigned<unsigned int      > : true_t {};
    template<> struct is_unsigned<unsigned long     > : true_t {};
    template<> struct is_unsigned<unsigned long long> : true_t {};

    //default is unsigned
    template<typename T> 
    struct to_unsigned : type_t<T>{};

    //specification where we check all possible signed combinations
    template<> struct to_unsigned<signed char     > : type_t<unsigned char     > {};
    template<> struct to_unsigned<signed short    > : type_t<unsigned short    > {};
    template<> struct to_unsigned<signed int      > : type_t<unsigned int      > {};
    template<> struct to_unsigned<signed long     > : type_t<unsigned long     > {};
    template<> struct to_unsigned<signed long long> : type_t<unsigned long long> {};


#endif //}

//forward definitions //{
#if true
    struct Point;
    std::ostream& operator<<(std::ostream& os, Point p);

    template <typename T, typename... Args> void debugHelper(int index, const char* funcInput, const T& input, const Args&... other);
    template <typename T>                   void debugHelper(int index, const char* funcInput, const T& input);
    
                                void debugHelper(int index, const char* funcInput, const char*  input);
                                void debugHelper(int index, const char* funcInput, char*        input);
                                void debugHelper(int index, const char* funcInput, char         input);
                                void debugHelper(int index, const char* funcInput, std::string& input);
    template <typename... Args> void debugHelper(int index, const char* funcInput, const char*  input, const Args&... other );
    template <typename... Args> void debugHelper(int index, const char* funcInput, char*        input, const Args&... other );
    template <typename... Args> void debugHelper(int index, const char* funcInput, char         input, const Args&... other );
    template <typename... Args> void debugHelper(int index, const char* funcInput, std::string  input, const Args&... other );
    
    bool checkstr(const char* text, int text_len,                     const char* find, int find_len, int find_i       = 0, bool ignore_case = 0, const char* custom_end = 0, bool exclude_end = 0, const char* custom_start = 0, bool exclude_start = 0);
    bool checkstr(const char* text,                                   const char* find,               int find_i       = 0, bool ignore_case = 0, const char* custom_end = 0, bool exclude_end = 0, const char* custom_start = 0, bool exclude_start = 0);
    int  findstr (const char* text, int text_len,                     const char* find, int find_len, int search_start = 0, bool ignore_case = 0, const char* custom_end = 0, bool exclude_end = 0, const char* custom_start = 0, bool exclude_start = 0, LINE_TRACKER);
    int  findstr (const char* text,                                   const char* find,               int search_start = 0, bool ignore_case = 0, const char* custom_end = 0, bool exclude_end = 0, const char* custom_start = 0, bool exclude_start = 0, LINE_TRACKER);

    template<typename T> typename enable_if< is_number<T>::value , void>::type printhex(T input);
    template<typename T> typename enable_if< is_number<T>::value , void>::type printbin(T input);
    template<typename T> typename enable_if< is_pointer<T>::value, void>::type printhex(T ptr);
    template<typename T> typename enable_if< is_pointer<T>::value, void>::type printbin(T ptr);
    template<typename T> typename enable_if<!is_number<T>::value && !is_pointer<T>::value, void>::type printhex(T input);
    template<typename T> typename enable_if<!is_number<T>::value && !is_pointer<T>::value, void>::type printbin(T input);
    template<typename T> typename enable_if< is_pointer<T>::value, int>::type getBinNumLen(T n);
    template<typename T> typename enable_if<!is_pointer<T>::value, int>::type getBinNumLen(T n);
    template<typename T> typename enable_if< is_pointer<T>::value, int>::type getHexNumLen(T n);
    template<typename T> typename enable_if<!is_pointer<T>::value, int>::type getHexNumLen(T n);

    constexpr static int8_t NO_INDEX = -2;
    template<typename T, typename UT = typename to_unsigned<T>::type> UT   get_bits(T  n,          int8_t i, int8_t iend = NO_INDEX);
    template<typename T, typename UT = typename to_unsigned<T>::type> void set_bits(T& n, UT bits, int8_t i, int8_t iend = NO_INDEX);

    void printlen(const char* str, int64_t len, LINE_TRACKER);
    double strToNum(const char* str, size_t len = SIZE_MAX);
    template<typename T> typename enable_if<!is_pointer<T>::value, int>::type getLen(T num);
    int getLen(std::string str);
    int getLen(const char* str);
    int getLen(double d); 
    int strcmp_tk(const char *s1, const char *s2);
    long long strlen_tk(const char* str)      ;
    void display_info(const char* input, int i, int iend = INT_MIN, bool ignore_multi_byte = false, bool align_next_line = false);
    void display_info(std::string input, int i, int iend = INT_MIN, bool ignore_multi_byte = false, bool align_next_line = false);
    template<typename... Args>
    void debug_banner_h(Args... args);
    void debug_banner_h();
    void debug_bound_h(int len, int i, LINE_TRACKER);
    template<typename Lambda> double strMath(const char* str, int len, Lambda extraWords);
    double strMath(const char* str, int len = -1);
    void delayMicroseconds(int u);
    void delay(int i);
    template<typename T> void printarray_h(T array, size_t size);
    template<typename T> void printarray_h(T array, size_t size, const char* inBetween);
    
    //empty print
    void print();
    void println();

    //default prints
    template<typename T> void print(const T& input) ;
    template<typename T, typename... Args> void print(const T& input, const Args&... other);
    template<typename T, typename... Args> void println(const T& input, const Args&... other);
    
    //print int8_t and uint8_t as numbers and not characters
    void print(uint8_t c);
    void print(int8_t c) ;
    template<typename... Args> void print(uint8_t c, const Args&... other);  
    template<typename... Args> void print(int8_t c, const Args&... other) ;
    void println(uint8_t c);
    void println(int8_t c) ;
    template<typename... Args> void println(uint8_t c, const Args&... other);
    template<typename... Args> void println(int8_t c, const Args&... other) ;

#endif //}

//ARRAY CLASS

template<typename T>
class Array
{
    public:
    T* array;
    unsigned int size;

    void add(T input, LINE_TRACKER)
    {
        // we allocate the size for the new array
        T* newArray = new T[size + 1];

        if(newArray == nullptr)
        {
            println(ERROR_LINE,"could not allocated memory for a new array of size ",size + 1);
            while(1);// bug finding
        }else
        {
            for (unsigned int i = 0; i < size; i++)
            {
                newArray[i] = array[i]; // we set the new array to the previous array
            }

            // we set the new value to add at the end
            newArray[size] = input;

            // we get rid of the previous array
            delete[] array;
            array = nullptr; // idk, just to be sure

            // set the array pointer to the new array pointer
            array = newArray;

            // we up the size by one
            size++;
        }
    }

    void remove()
    {
        // we allocate the size for the new array
        T* newArray = new T[size - 1];

        for (unsigned int i = 0; i < size - 1; i++)
        {
        newArray[i] = array[i]; // we set the new array to the previous array
        }

        // we get rid of the previous array
        delete[] array;
        array = nullptr; // idk, just to be sure

        // set the array to the new array
        array = newArray;

        // we up the size by one
        size--;
    }

    void remove(unsigned int index)
    {
        // we allocate the size for the new array
        T* newArray = new T[size - 1];

        for (unsigned int i = 0; i < index; i++)
        {
            newArray[i] = array[i]; // we set the new array to the previous array
        }

        for (unsigned int i = index; i < size - 1; i++)
        {
            newArray[i] = array[i + 1]; // we set the new array to the previous array
        }

        // we get rid of the previous array
        delete[] array;
        array = nullptr; // idk, just to be sure

        // set the array to the new array
        array = newArray;

        // we up the size by one
        size--;
    }

    T at(unsigned int index, LINE_TRACKER)
    {
        // if the index is in bound
        if (0 <= index && index <= size - 1)
        {
            return array[index];
        }else
        {
            println(ERROR_LINE,"invalid index (the index you gave doesn't point to an element in the array)");
            while(1);// bug finding
            return 0;
        }
    }

    T operator[](unsigned int index) {
        return array[index];
    }

    Array()
    {
        //variable initializations (note to self, add this in front of any and all cosntructors)
        this->array = nullptr;
        this->size = 0;
    };
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    ~Array()
    {
        delete[] array; // remove array from the memory
    }
};

//ARRAY CLASS


//NEW PARSER CLASS !!!

//automatically add a '\0' at the ends of strings that don't have one (transform char* string in std::string in the process for convenience)
std::string to_str(const char* str, int len) {
    //temporary fast buffer
    char* buff = new char[len + 1];

    //copy over argument
    for(int j = 0; j < len; j++) {
        buff[j] = str[j];
    }
    buff[len] = '\0';

    //set string to fast buffer
    std::string new_str = buff;

    //no memory leaks
    delete[] buff;

    //return newly created string
    return new_str;
}



struct Snippet;

class Parser {
    public:

    //struct for singular argument, containing the index and length inside of the str variable
    struct Arg {
        int i  ;//the index at which the argument starts in the string provided to the parser
        int len;//the length of the argument

        bool operator==(Arg o) {return o.i == i && o.len == len;}
        bool operator!=(Arg o) {return o.i != i || o.len != len;}

        bool undef_error(LINE_TRACKER) const {
            if(i == -1 && len == -1) {
                println(ERROR_LINE,"operation on undefined Parser::Arg (i.e. on an Argument that's equal to {-1, -1})");
                return true;
            }
            return false;
        }

        std::string to_str(const char* origin_str, int origin_str_len, LINE_TRACKER) const {
            if(undef_error(LINE_TRACKER_INPUT)) return "";
            return ::to_str(origin_str, origin_str_len);
        }
        std::string to_str(const char* origin_str, LINE_TRACKER) const {
            if(undef_error(LINE_TRACKER_INPUT)) return "";
            return ::to_str(origin_str + i, len);
        }
        std::string to_str(std::string origin_str, LINE_TRACKER) const {
            if(undef_error(LINE_TRACKER_INPUT)) return "";
            return to_str(origin_str.c_str(), LINE_TRACKER_INPUT);
        }

        //legacy transform: transforms the current object into a "Snippet" struct (used to get the start and end index of the argument)
        Snippet to_start_end() const;
        operator Snippet() const;

        Arg(int i, int len) : i(i), len(len) {}
        Arg()               : i(-1), len(-1) {}
    
        static const Arg UNDEF;
    };

    //custom args struct to return multiple arguments
    struct Args {
        Arg* v;
        int  c;
    };

    //make a variable to remember if we found a command
    static constexpr const char* name_char = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int8_t      final_parse    = 0;//if we currently are in the last  parsing step
    int8_t      initial_parse  = 1;//if we currently are in the first parsing step
    int8_t      in_char        = 0;//if we are in a string              e.g. 'in a character'
    int8_t      in_str         = 0;//if we are in a string              e.g. "in a string"
    int8_t      in_sl_comment  = 0;//if we are in a single line comment e.g. "//I am a single line comment"
    int8_t      in_ml_comment  = 0;//if we are in a multi  line comment e.g. "/*I am a multi line comment*/"
    int8_t      entered_char   = 0;//if we JUST entered a char
    int8_t      entered_str    = 0;//if we JUST entered a char
    int8_t      par_lev        = 0;//parenthesis level                  e.g. (in a parenthesis)
    int8_t      brace_lev      = 0;//brace level                        e.g. {in a brace}
    int8_t      bracket_lev    = 0;//bracket level                      e.g. [in a bracket]
    int&        k                 ;//the index of the string (as a reference)
    const char* str            = 0;//the string we are currently parsing
    Arg         argv[15]          ;//make array for arguments
    int         argc           = 0;//number of arguments in the array
    int         g_i            = 0;//a global index  variable (this variable indicates to the parser the starting index       it should be allowed to look at)
    int         g_len          = 0;//a global length variable (this variable indicates to the parser the length of the string it should be allowed to look at)

    void debugParser(int ms = 100) {
        println();
        display_info(str, k, k, 1); 
        println(
            "initial_parse = ", initial_parse, "\n", 
            "in_char       = ", in_char      , "\n", 
            "in_str        = ", in_str       , "\n",
            "in_sl_comment = ", in_sl_comment, "\n",
            "in_ml_comment = ", in_ml_comment, "\n",
            "entered_char  = ", entered_char , "\n",
            "entered_str   = ", entered_str  , "\n",
            "par_lev       = ", par_lev      , "\n",
            "brace_lev     = ", brace_lev    , "\n",
            "bracket_lev   = ", bracket_lev  
        );
        delay(ms);
    }
    
    bool parse(LINE_TRACKER) {

        //if we are one before k becomes len (we are at final parse) since the start of the parse function will turn k into len
        if(k == g_i + g_len - 1) {
            //set final parse to true
            final_parse = 1;
        }else if(k >= g_i + g_len - 1) {
            //automatically return when outside of the bounds of the string
            return false;
        }

        //get current character 
        char c = str[k];
        if(initial_parse == 0) {
                
            //if we are leaving a parenthesis (that isn't in a char)
            if      (c == ')' && is_raw()) {
                //decrease parenth level
                par_lev--;
            
            //if we are leaving a brace (that isn't in a char or str)
            }else if(c == '}' && is_raw()) {
                //decrease parenth level
                brace_lev--;

            //if we are leaving a bracket (that isn't in a char)
            }else if(c == ']' && is_raw()) {
                //decrease parenth level
                bracket_lev--;
            }

            //if we are leaving a char (and if we didn't enter a char)
            if      (c == '\'' && in_char == 1 && entered_char == 0 && in_str  == 0 && !is_comment()) {
                //get index of last backslash
                int i = (k - 1);
                while(g_i <= i && str[i] == '\\') i--;
                i++;
                
                //get number of backslashes based on index
                int n_of_backslashes = (k - 1) - i + 1;
                
                //if the number of backslashes is even we are getting out of a char
                if(n_of_backslashes % 2 == 0) {
                    //update in char to make sure we know we are out of a char
                    in_char = 0;
                }

            //if we are leaving a str (and if we didn't enter a str)
            }else if(c == '\"' && in_str  == 1 && entered_str  == 0 && in_char == 0 && !is_comment()) {
                //get index of last backslash
                int i = (k - 1);
                while(g_i <= i && str[i] == '\\') i--;
                i++;
                
                //get number of backslashes based on index
                int n_of_backslashes = (k - 1) - i + 1;
                
                //if the number of backslashes is even we are getting out of a str
                if(n_of_backslashes % 2 == 0) {
                    //update in char to make sure we know we are out of a str
                    in_str = 0;
                }
            }

            //if we are leaving a single line comment
            if      (k + 1 < strlen_tk(str) && str[k + 1] == '\n' && !is_str() && in_ml_comment == 0 && in_sl_comment == 1) {
                //get index of last backslash
                int i = (k - 1);
                while(g_i <= i && str[i] == '\\') i--;
                i++;
                
                //get number of backslashes based on index
                int n_of_backslashes = (k - 1) - i + 1;
                
                //if the number of backslashes is even we are getting out of a single line comment (otherwise its a line continuation)
                if(n_of_backslashes % 2 == 0) {
                    //update in char to make sure we know we are out of a char
                    in_sl_comment = 0;
                }
            
            //if we are leaving a multi line comment
            }else if(k >= 1 && checkstr(str, "*/", k - 1) && !is_str() && in_ml_comment == 1 && in_sl_comment == 0) {
                in_ml_comment = 0;
            }
            
            
            //increase index
            k++;
        }else {
            //disable initial parse after first initial parse
            initial_parse = 0;
        }
        
        if(final_parse   == 0) {
           
            //128 up to 191
            while(0x80 <= (uint8_t)(str[k]) && (uint8_t)(str[k]) <= 0xBF) {
                k++;//skip the continuation byte of multi byte characters
            }

            //get current character 
            c = str[k];

            //reset entered string and char
            entered_char = 0;
            entered_str  = 0;
            
            //if we are entering a single line comment
            if      (checkstr(str, "//", k) && is_raw()) {
                in_sl_comment = 1;
            
            //if we are entering a multi line comment
            }else if(checkstr(str, "/*", k) && is_raw()) {
                in_ml_comment = 1;
            }
            
            //if we are entering a char
            if      (c == '\'' && is_raw()) {
                //update in char to make sure we know we are in a char
                in_char = 1;
                entered_char = 1;//tell things that we are entering a string (do not close immediatly after)

            //if we are entering a string
            }else if(c == '\"' && is_raw()) {
                //update in string to make sure we know we are in a string
                in_str = 1;
                entered_str = 1;//tell things that we are entering a string (do not close immediatly after)
            }

            //if we are entering a parenthesis (that isn't in a char or a str or in a comment)
            if      (c == '(' && is_raw()) {
                //increase parenth level
                par_lev++;
            
            //if we are entering a brace (that isn't in a char or a str)
            }else if(c == '{' && is_raw()) {
                //increase parenth level
                brace_lev++;
            
            //if we are entering a bracket (that isn't in a char or a str)
            }else if(c == '[' && is_raw()) {
                //increase parenth level
                bracket_lev++;
            }

        }else {
            return false;
        }

        return true;
    }

    /** 
     * @retval returns a boolean that represents wether or not the current character could be found in a name
     */
    bool is_name(int k = INT_MIN) {
        //if we didn't initialize the index, set to default
        if(k == INT_MIN) {
            k = this->k;
        }

        //if we are out of bounds, then auto false
        if(k < 0 || strlen_tk(str) <= k) {
            return false;
        }

        //check for a character that could be contained in a name
        for(int i = 0; name_char[i] != '\0'; i++) {
            if(str[k] == name_char[i]) {
                //found a name return true
                return true;
            }
        }

        //did not find a name
        return false;
    }

    Arg find_name(int inc) {
        // make copy of current inde
        int l = k;
        int str_len = strlen_tk(str); //no need to re calculate strlen every time
        
        // skip up to first name character (assuming no comments)
        while(!is_name(l)) {
            l += inc;
            
            //if the l is out of bounds, return empty (means we didn't find any name to begin with) 
            if(l < 0 || str_len <= l) {
                return {0, 0};//return empty argument
            }
        }

        // set start of the name (could be end if searching with inc of -1 (will fix later))
        int start = l;

        // skip up to the first non name character
        while(is_name(l)) {
            l += inc;
        }

        // set end of the name
        int end = l - inc;

        //invert start and end if we were searching backwards (with negative inc)
        if(inc < 0) {
            int start_copy = start;
            start = end;
            end = start_copy;
        }

        //get lenght of the found string
        int len = end - start + 1;

        //return the start index and the length of the found string
        return {start, len};
    }

    Args parseArgs(LINE_TRACKER) {

        if(str == nullptr) {
          println(ERROR_LINE,"str is a nullptr");
          while(1) delay(1000);
          return {0, 0};
        }

        //reset argument count
        argc = 0;

        int8_t i_par_lev     = par_lev    ;//initial parenthesis level : copy parenthesis level to compare levels to this
        int8_t i_brace_lev   = brace_lev  ;//initial brace level
        int8_t i_bracket_lev = bracket_lev;//initial bracket level
        int8_t i_k           = k          ;//initial k index           : copy the k (index) before the search for arguments

        //parse until we reach a parenthesis or the end of the string
        while(par_lev == i_par_lev && k < g_i + g_len) {
            parse();
        } 

        //diagnose errors : 
        //reached the end of the string or end of a parenthesis
        if(k >= g_i + g_len || par_lev < i_par_lev) {
            //print errors and visual explaination to user
            println(ERROR_LINE,"could not find parenthesis to start arguments search : ");
            display_info(str, i_k, k - 1 + 1);
            
            //return pointer to nothing and count = 0 (no arguments)
            return {0, 0};
        }

        // The Inner Workings of The Argument Parsing Algorithm : 
        //   we found the "(" parenthesis to start the argument search
        //   lets go forward until we find either the end of that parenthesis (e.g. ")") or a comma (e.g. ",")
        //   repeat this until we found the end parenthesis            
        
        //make variable to store last comma (set default to current index which is the start parenthesis : "(")
        int last_comma = k;
        
        //while we are inside the parenthesis
        while(true) {
            //parse the string
            parse();
            
            //check if we found a comma (not in a string or a comment)
            if(
                ((str[k] == ',') || (str[k] == ')')) &&                                                  //found a comma 
                !in_str && !in_char &&                                                                 //not in some sort of string
                par_lev == (i_par_lev + 1) && brace_lev == i_brace_lev && bracket_lev == i_bracket_lev //did not enter or leave specific parenth/bracket/brace level
            ) {

                //get start and end index of argument
                int start = last_comma + 1;//one character after the last comma
                int end   = k - 1         ;//one character before the current comma we found

                
                //skip all new lines for start
                while(str[start] == '\n' || str[start] == ' ') start++; 

                //figure out the index and length of the message 
                int arg_i   = start;
                int arg_len = end - start + 1;

                
                //if we ran out of arguments storage print error
                if(argc >= sizeofarray(argv)) {
                    //print error + comprehensible visual to explain at which argument the error happent
                    println(ERROR_LINE,"ran out of argument storage (max argument (",sizeofarray(argv),"), now at argument ",argc + 1,") at index ",arg_i);
                    display_info(str, start, end);
                    
                    //get out of the loop (can't search for arguments anymore, we don't have enough storage)
                    break;
                }


                //set argument (store index and length of argument) 
                argv[argc].i   = arg_i  ;
                argv[argc].len = arg_len;

                //increase argc counter since we added an argument
                argc++;

                //update last comma (set to current index)
                last_comma = k;

                //if we just found a parenthesis get out of this loop
                if(str[k] == ')') {
                    break;
                }
            }
        }

        //return all the arguments we found
        return {argv, argc};
    }

    //returns index and length of the string 
    Arg getStrArg(Arg arg) {

        //check for parenthesis first (do they match all the way)
        {
            int i = arg.i;//make copy of arg.i
            //check if those parenthesis actually "connect" to do so, we create another parser (specify the start and length of the search)
            Parser p(str, i, arg.i, arg.len);

            //iterate through the whole thing until we reach the end
            int last_par_lev = 0;
            while(p.parse()) {
                //if we found early end of the parenthesis (e.g. string was : "(some parenthesis) + (some other parenthesis)")
                //                                                                              ^ 
                //                                                                  becomes zero here so leaves

                //if the parenthesis level changed and its smaller or equal to zero then something aint adding up
                if(p.par_lev <= 0 && last_par_lev != p.par_lev) {
                    //print detailed error explaining how we got out of a parenthesis prematurely
                    print("ERROR, early ending parenthesis at index ");
                    print((i - 1));
                    print(" in string \"");
                    printlen(str + arg.i, arg.len);
                    println("\"");
                    display_info(str + arg.i, (i - 1) - arg.i);
                    return {0, 0};
                }

                last_par_lev = p.par_lev;
            }

            //if the number of parenthesis all canceled out to zero (meaning we had as much "(" as ")")
            if(p.par_lev != 0) {
                //if we don't have the right number to cancel the parenthesis get out of the function
                print("ERROR, \"");
                print((p.par_lev < 0)?("too many parenthesis"):("missing parenthesis"),"in string \"");
                printlen(str + arg.i, arg.len);
                println("\" at indexes ",arg.i," and ",arg.i + arg.len - 1,")");
                display_info(str, arg.i);
                display_info(str, arg.i + arg.len - 1);
                return {0, 0};
            }
        }

        //ignore spaces and parenthesis incompassing the whole string
        while(true) {
            //get rid of spaces at the front
            if(str[arg.i] == ' ') {
                arg.i   += 1;
                arg.len -= 1;

            //get rid of spaces at the end
            }else if(str[arg.i + arg.len - 1] == ' ') {
                arg.len -= 1;
                
            //get rid of any parenthesis encompassion the whole string
            }else if(str[arg.i] == '(' && str[arg.i + arg.len - 1] == ')') {                

                int i = arg.i;//make copy of arg.i
                //check if those parenthesis actually "connect" to do so, we create another parser (specify the start and length of the search)
                Parser p(str, i, arg.i, arg.len);

                //iterate through the whole thing until we reach the end
                while(p.parse()) {
                    //if we found early end of the parenthesis (e.g. string was : "(some parenthesis) + (some other parenthesis)")
                    //                                                                              ^ 
                    //                                                                  becomes zero here so leaves
                    
                    if(p.par_lev <= 0) {
                        //print detailed error explaining how we got out of a parenthesis prematurely
                        print("ERROR, \"");
                        printlen(str + arg.i, arg.len);
                        println("\" ");
                        display_info(str, arg.i);
                        display_info(str, arg.i + arg.len - 1);
                        return {0, 0};
                    }
                }

                //if the number of parenthesis all canceled out to zero (meaning we had as much "(" as ")")
                if(p.par_lev == 0) {
                    //get rid of the encompassing parenthesis :
                    arg.i   += 1;
                    arg.len -= 2;
                }else {
                    //if we don't have the right number to cancel the parenthesis get out of the function
                    print("ERROR, \"");
                    print((p.par_lev < 0)?("too many parenthesis"):("missing parenthesis"),"in string \"");
                    printlen(str + arg.i, arg.len);
                    println("\" at indexes ",arg.i," and ",arg.i + arg.len - 1,")");
                    display_info(str, arg.i);
                    display_info(str, arg.i + arg.len - 1);
                    return {0, 0};
                }
            }else {
                //if none of the stuff was done, then get out of the loop
                break;
            }
        }

        //check if the string we recieved (after clearing all useless parenthesis and spaces) has double quotes around it (is it a string)
        if((str[arg.i] == '\"' || str[arg.i] == '\'') && (str[arg.i + arg.len - 1] == '\"' || str[arg.i + arg.len - 1] == '\'')) {
            //make yet another parser, this time to check the validity of the string
            int i = arg.i;//make copy of arg.i
            //check if those parenthesis actually "connect" to do so, we create another parser (specify the start and length of the search)
            Parser p(str, i, arg.i, arg.len);

            bool is_valid  = true;

            //iterate through the whole thing until we reach the end
            while(p.parse()) {
                //if we got out of any string than its an invalid string
                if(!p.in_str && !p.in_char) {
                    is_valid  = false;
                    break; 
                }
            }

            //if the string is a valid one, get rid of surrounding quotes and ship it
            if(is_valid) {
                //get rid of surrounding quotes
                arg.i   += 1;
                arg.len -= 2;

                //ship it
                return arg;
            }else {
                //we didn't find a valid string, print an error
                print("ERROR, \"");
                printlen(str + arg.i, arg.len);
                println("\" was not a valid string (double quotes close prematurely at index ",i,")");
                display_info(str, i);
                return {0, 0};
            }
        }else {
            print("ERROR, \"");
            printlen(str + arg.i, arg.len);
            println("\" was not a valid string (missing quotes at indexes ",arg.i," and ",arg.i + arg.len - 1,")");
            display_info(str, arg.i);
            display_info(str, arg.i + arg.len - 1);
            return {0, 0};
        }

        return arg;
    }

    //returns a god damn double number thingy whatever
    double getNumArg(Arg arg) {
        double result = strMath(str + arg.i, arg.len);
        return result;
    }

    void reset(int k) {
        initial_parse = 1;
        in_char       = 0;
        in_str        = 0;
        entered_char  = 0;
        entered_str   = 0;
        par_lev       = 0;
        brace_lev     = 0;
        bracket_lev   = 0;
        k             = k;
        argc          = 0;
    }

    // states {
    #if true



        //is the character at the current index RAW, meaning its not some sort of string or comment
        bool is_raw() {
            return !in_str && !in_char && !in_sl_comment && !in_ml_comment;
        }
        
        //is the character at the current index RAW bracketwise, meaning if its not inside of any kind of bracket (e.g. brace : "{}", parenthesis : "()", brackets : "[]")
        bool is_raw_bracket() {
            return par_lev == 0 && brace_lev == 0 && bracket_lev == 0;
        }

        //is the character at the current index any sort of string (this includes characters, e.g. 'works with single quote strings')
        bool is_str() {
            return in_str || in_char;
        }
        
        //is the character at the current index any sort of comment
        bool is_comment() {
            return in_sl_comment || in_ml_comment;
        }


    
    #endif
    // }

    //constructor which you can specify the string and the index
    Parser(const char* str, int& index, LINE_TRACKER) : k(index), str(str), g_i(0) {
        g_len = strlen_tk(str);//set length to the string length

        if(str == nullptr) {
            println(ERROR_LINE,"the string you specified in the parser was a nullptr");
        }
    }
    Parser(const char* str, int& index, int g_i, int g_len) : k(index), str(str), g_i(g_i), g_len(g_len) {}
};

struct Snippet {
    int start;
    int end  ;

    operator Parser::Arg() {return {start, end - start + 1};}
    Snippet(Parser::Arg arg) : start(arg.i), end(arg.i + arg.len - 1) {}
    Snippet(int start, int end) : start(start), end(end) {}
};

const Parser::Arg Parser::Arg::UNDEF = Parser::Arg{-1, -1};
Snippet Parser::Arg::to_start_end() const {
    return {i, i + len - 1};
} 
Parser::Arg::operator Snippet () const {
    return {i, i + len - 1};
}


//print Parser::Arg as a normal string
void print(const char* str, Parser::Arg arg)                                                   ;
template<typename... Args> void print(const char* str, Parser::Arg arg, const Args&... other)  ;
void println(const char* str, Parser::Arg arg)                                                 ;
template<typename... Args> void println(const char* str, Parser::Arg arg, const Args&... other);

void print(char* str, Parser::Arg arg)                                                   ;
template<typename... Args> void print(char* str, Parser::Arg arg, const Args&... other)  ;
void println(char* str, Parser::Arg arg)                                                 ;
template<typename... Args> void println(char* str, Parser::Arg arg, const Args&... other);

void print(Parser::Arg arg)                                                   ;
template<typename... Args> void print(Parser::Arg arg, const Args&... other)  ;
void println(Parser::Arg arg)                                                 ;
template<typename... Args> void println(Parser::Arg arg, const Args&... other);

void display_info(const char*  input, Parser::Arg arg, bool ignore_multi_byte = false, bool align_next_line = false);
void display_info(std::string& input, Parser::Arg arg, bool ignore_multi_byte = false, bool align_next_line = false);

bool checkstr(const char* text, int text_len, const char* origin, Parser::Arg find,               int find_i       = 0, bool ignore_case = 0, const char* custom_end = 0, bool exclude_end = 0, const char* custom_start = 0, bool exclude_start = 0);
bool checkstr(const char* text,               const char* origin, Parser::Arg find,               int find_i       = 0, bool ignore_case = 0, const char* custom_end = 0, bool exclude_end = 0, const char* custom_start = 0, bool exclude_start = 0);
int  findstr (const char* text, int text_len, const char* origin, Parser::Arg find,               int search_start = 0, bool ignore_case = 0, const char* custom_end = 0, bool exclude_end = 0, const char* custom_start = 0, bool exclude_start = 0, LINE_TRACKER);
int  findstr (const char* text,               const char* origin, Parser::Arg find,               int search_start = 0, bool ignore_case = 0, const char* custom_end = 0, bool exclude_end = 0, const char* custom_start = 0, bool exclude_start = 0, LINE_TRACKER);


//NEW PARSER CLASS!!!

// other functions {
#if true


void delay(int i)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(i));
}
void delayMicroseconds(int u) {
    std::this_thread::sleep_for(std::chrono::microseconds(u));
}
long long millis()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
uint64_t micros() {
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(now).count();
}
long long seconds() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}


void println() {
    std::cout<<std::endl;
}
template<typename T> void println(const T& input) {
    std::cout<<input<<std::endl;
}



// commands for print statements
namespace PrintCmds 
{

    struct Cmds {
        unsigned int order;                                   // the order in which it should be looked for in the string
        const char* cmd;                                      // string specifying the command (e.g. "%l")
        int id;                                               // the command id                (e.g. "ALIGN")
    };

    enum CmdIds {
        ALIGN,
        PRINT_BIN,
        PRINT_HEX,
    };

    Cmds cmds[] = {
        {0, "%l", ALIGN    },
        {0, "%b", PRINT_BIN},
        {0, "%x", PRINT_HEX},
    };

    namespace Printing  {
        enum Printing {
            HEX   ,
            BIN   ,
            NORMAL,
        };
        Printing printing  = NORMAL;    
    };

    namespace Alignment {
        enum Alignment{
            NOT_ALIGNED, 
            ALIGNED    ,
        };
        Alignment   alignment  = NOT_ALIGNED;
        int         len        = 10         ;
        double      mode       = 1          ;
        const char* start      = ""         ; int start_len      = 0;
        const char* end        = ""         ; int end_len        = 0;
        const char* fill_left  = " "        ; int fill_left_len  = 1;
        const char* fill_right = " "        ; int fill_right_len = 1;

        void debug() {
            DEBUG_BANNER("Alignment variables : ");
            DEBUG(
                alignment ,
                len       ,
                mode      ,
                start     ,
                end       ,
                fill_left ,
                fill_right
            );
        }
    };

    //forward declare playcmd
    template<typename T> int playcmd(T input, const char* str, int k, Cmds curr_cmd);

    struct CmdInfo {
        int i   ;//the start index of the cmd that got played
        int iend;//the end index of the cmd that got played
        int id  ;//the id of the command that got played
    };

    CmdInfo played_cmds[10];
    int played_count;

    void print_played_cmds() {
        for(int i = 0; i < played_count; i++) {
            println("[",i,"] = {i:",played_cmds[i].i,", iend:",played_cmds[i].iend,", id:",played_cmds[i].id,"}");
        }
    }

    template<typename T>
    void printcmd(T input, const char* str) {
        //reset played commands count
        played_count = 0;
        Printing::printing   = Printing::NORMAL  ;
        Alignment::alignment = Alignment::ALIGNED;

        //variables to store the minimum and maximum values of order in the cmd array
        unsigned int min_o = UINT_MAX;
        unsigned int max_o = UINT_MIN;

        //find min and max for order
        for(int i = 0; i < (int)(sizeofarray(cmds)); i++) {
            //get current order
            int o = cmds[i].order;
            
            //update the minimum and maximum orders
            if(o < min_o) min_o = o;
            if(o > max_o) max_o = o;
        }

        //make global index variable representing the first non command character
        int k = 0;

        //go through all of the order values between min_o and max_o
        for(int o = min_o; o <= max_o; o++) {     
            //go through all of the cmd array
            for(int i = 0; i < sizeofarray(cmds); i++) {

                //if order matches
                if(cmds[i].order == o) {
                    //search until you find all occurence of said command
                    int f_i = 0;
                    while(str[f_i] != '\0') {


                        //search at f_i index
                        f_i = findstr(str, cmds[i].cmd, f_i);

                        //if we didn't find anything, get out
                        if(f_i == -1) break;

                        //play said command and store what the command wants to hide from the final print
                        int end_cmd_i = playcmd(input, str, f_i, cmds[i]);

                        if(end_cmd_i < f_i || strlen_tk(str) <= end_cmd_i) {
                            println("ERROR line ",__LINE__," in ",__FILE__,", the return index (",end_cmd_i,") of the command \"",cmds[i].cmd,"\" of id:",cmds[i].id," is out of bounds (range is ",f_i,":",strlen_tk(str) - 1,")");
                            display_info(str, f_i, end_cmd_i - f_i + 1);
                            end_cmd_i = f_i;//ignore the command completely
                            // for(int z = 0; z < f_i; z++) print(" "); 
                            // for(int z = f_i; z < end_cmd_i - f_i + 1; z++) print("^");
                            // println();
                            // for(int z = 0; z < f_i; z++) print(" "); 
                            // println("(not in this range)");
                            // println();
                        }

                        //if we have the size for a command to enter the list
                        if(played_count < sizeofarray(played_cmds)) {
                                
                            //add command to a list
                            played_cmds[played_count].i    = f_i       ;
                            played_cmds[played_count].iend = end_cmd_i ;
                            played_cmds[played_count].id   = cmds[i].id;

                            //update played_count
                            played_count++;

                        }else {
                            println("ERROR line ",__LINE__," in ",__FILE__,", was not able to store the ",played_count + 1,"th command \"",cmds[i].cmd,"\" at index ",f_i);
                            display_info(str, f_i, f_i + strlen_tk(cmds[i].cmd) - 1);
                        }

                        //update f_i to skip command we just found
                        f_i += strlen_tk(cmds[i].cmd);
                    }
                }
            }
        }
    

        //do alignment stuff if selected aligned        
        int align_space;
        int left_space;
        if(Alignment::alignment == Alignment::ALIGNED) {

            //get length of number we are about to print
            int numLen = 0;
            if      (Printing::printing == Printing::NORMAL) {
                numLen = getLen(input);
            }else if(Printing::printing == Printing::BIN) {
                numLen = getBinNumLen(input);
            }else if(Printing::printing == Printing::HEX) {
                numLen = getHexNumLen(input);
            }

            //number of spaces we need to add for alignment (in total)
            align_space = Alignment::len - numLen;

            //get specific number of spaces for before the number
            left_space = (double)(align_space) * (Alignment::mode);

            //print custom alignment text (start and fill)
            if(Alignment::fill_left_len != 0) {
                //print the custom fill_left
                for(int i = 0; i < left_space; i++) {
                    int truei = i % Alignment::fill_left_len;
                    print(Alignment::fill_left[truei]);
                }

                //print the custom start
                printlen(Alignment::start, Alignment::start_len);
            }else {
                println("ERROR, fill_left specifier length is zero");
            }
        }

        //print the input
        if      (Printing::printing == Printing::NORMAL) {
            print(input);
        }else if(Printing::printing == Printing::BIN) {
            printbin(input);
        }else if(Printing::printing == Printing::HEX) {
            printhex(input);
        }

        //do alignment stuff if selected aligned
        if(Alignment::alignment == Alignment::ALIGNED) {
            //get remaining number of spaces to place after the number
            int right_space = align_space - left_space;

            //print custom alignment text (end and fill)
            if(Alignment::fill_right_len != 0) {
                //print the custom end
                printlen(Alignment::end, Alignment::end_len);

                //print the custom fill_left
                for(int i = 0; i < right_space; i++) {
                    int truei = i % Alignment::fill_right_len;
                    print(Alignment::fill_right[truei]);
                }
            }else {
                println("ERROR, fill_end specifier length is zero");
            }
        }

        //print the rest of the string
        
        int start = 0;
        int end   = 0;

        //loop to print all the in betweens of the commands
        while(true) {
                
            //we are going to want to find the array index of the command with the smallest string index (ignore indexs that are before start, that would fuck up the printing)
            int  min_arr_i      = 0;
            bool done_printing  = true;

            //go through all of the played_cmds array
            for(int i = 0; i < played_count; i++) {

                //if the current array index's string index is higher than the start (end of last index we printed) then we still have to print (set done printing to false)
                if(start <= played_cmds[i].i) {
                    //we still have to print (set done printing to false)
                    done_printing = false;
                    
                    //if the current array index is smaller than the min_arr_i update variable
                    if(played_cmds[i].i < played_cmds[min_arr_i].i) {
                        min_arr_i = i; 
                    }
                }

            }

            //if we are done printing get out of the loop
            if(done_printing) {
                break;
            }

            //update end (min cmd string index (-1 to move one before command (we don't print the command)))
            end = played_cmds[min_arr_i].i - 1;

            
            //figure out the length we need to print
            int len = end - start + 1;
            
            //print the bit in between the command
            printlen(str + start, len);

            //update start for next command (+1 to go after command (we don't print the command))
            start = played_cmds[min_arr_i].iend + 1;
            

            //get rid of the command at the min_arr_i we just used, push the other ones back and update the count
            for(int j = min_arr_i; j < (int)(sizeofarray(played_cmds)) - 1; j++) {
                //move elements one index down
                played_cmds[j] = played_cmds[j + 1];
            }

            //update the count (decrease we got rid of an element)
            played_count--;



        }
    
        //figure out things for last print
        end = strlen_tk(str) - 1;
        int len = end - start + 1;

        //print the last thing (connect start and actuall end of the string)
        printlen(str + start, len);
    }

    template<typename T>
    int playcmd(T input, const char* str, int k, Cmds curr_cmd) {

        //get elements from the current command
        int          id  = curr_cmd.id   ;
        const char*  cmd = curr_cmd.cmd  ;
        unsigned int o   = curr_cmd.order;


        if(id == ALIGN) {
            //set i to k + right after the command
            k += strlen_tk(cmd);
            int i = k;

            //create a basic parser
            Parser p(str, i);

            p.parse();

            int         len        = 10 ;
            double      mode       = 1  ;
            const char* start      = "" ; int start_len      = -1;
            const char* end        = "" ; int end_len        = -1;
            const char* fill_left  = " "; int fill_left_len  = -1; 
            const char* fill_right = " "; int fill_right_len = -1; 


            //if the parenthesis level increased (found a parenthesis)
            if(p.par_lev > 0) {
                //reset parser and parse the arguments (reset to k)
                p.reset(k);

                //get arguments
                auto args = p.parseArgs();

                // align command specifications
                // %l
                // %l([len])
                // %l([len], [mode])
                // %l([len], [mode], [start])
                // %l([len], [mode], [start], [end])
                // %l([len], [mode], [start], [end], [fill])
                // %l([len], [mode], [start], [end], [fill_left], [fill_right]) //last one to specify filling
                
                if(0 < args.c) {
                    double num = p.getNumArg(args.v[0]);
                    
                    if(IS_VALID(num)) {
                        len = num;
                    }
                }
                if(1 < args.c) {
                    double num = p.getNumArg(args.v[1]);
                    
                    if(IS_VALID(num)) {
                        mode = num;
                    }
                }
                if(2 < args.c) {
                    auto   arg = p.getStrArg(args.v[2]);
                    
                    if(arg.len > 0) {
                        start     = p.str + arg.i;
                        start_len = arg.len;
                    }
                }
                if(3 < args.c) {
                    auto   arg = p.getStrArg(args.v[3]);
                    
                    if(arg.len > 0) {
                        end     = p.str + arg.i;
                        end_len = arg.len;
                    }
                }
                if(5 < args.c) {
                    auto   arg1 = p.getStrArg(args.v[4]);
                    auto   arg2 = p.getStrArg(args.v[5]);
                    
                    if(arg2.len > 0) {
                        fill_left      = p.str + arg1.i;
                        fill_left_len  = arg1.len;
                        fill_right     = p.str + arg2.i;
                        fill_right_len = arg2.len;
                    }
                }else if(4 < args.c) {
                    auto   arg = p.getStrArg(args.v[4]);
                    
                    if(arg.len > 0) {
                        fill_left      = p.str + arg.i;
                        fill_left_len  = arg.len;
                        fill_right     = p.str + arg.i;
                        fill_right_len = arg.len;
                    }
                }
            
            //if we don't have a parenthesis for aguments, look for a raw number all on its own, if there isn't a number than we go default everything
            }else if(ISNUMBER(str[i])){
                //set start of the number to k
                int s_i = i;//start index (start of the number)

                //continue until we reach something other than a number
                while(p.parse()) {
                    if(!ISNUMBER(str[i])) {
                        break;
                    }
                }

                //k is now equal to index of last digit + 1
                int e_i = i - 1;//end   index (end   of the number)

                //figure out the length of the number
                int n_len = e_i - s_i + 1;

                //get the number with strmath
                double result = strMath(str + s_i, n_len);

                //if the result is valid (e.g. not infinity or nan)
                if(IS_VALID(result)) {
                    //set the length to result
                    len = result;
                }

                //decrease k by to go back to last seen digit (will return k later)
                k--;
            }else if(p.in_str || p.in_char) {
                //set start index to k (start of the string)
                int s_i = i;

                //go forward until we find the end of the string
                while(p.parse()) {
                    if((!p.in_str && !p.in_char) || p.entered_str || p.entered_char) {
                        break;
                    }
                }

                //i is now equal to the index of the last quote + 1
                int e_i = i - 1;
                int arg_len = e_i - s_i + 1;

                //get the string
                Parser::Arg arg = p.getStrArg({s_i, arg_len});

                //get the value of the math inside that string
                double result = strMath(str + arg.i, arg.len);

                //if the result was valid use it for len
                if(IS_VALID(result)) {
                    len = result;
                }
            }
        
            
            //set the lengths if they are -1
            if(start_len      == -1) start_len      = strlen_tk(start     );                            
            if(end_len        == -1) end_len        = strlen_tk(end       );                        
            if(fill_left_len  == -1) fill_left_len  = strlen_tk(fill_left );                        
            if(fill_right_len == -1) fill_right_len = strlen_tk(fill_right);      
            
            //set alignment stuff
            Alignment::alignment      = Alignment::ALIGNED    ;
            Alignment::len            = len                   ; 
            Alignment::mode           = mode                  ; 
            Alignment::start          = start                 ;
            Alignment::start_len      = start_len             ; 
            Alignment::end            = end                   ;
            Alignment::end_len        = end_len               ; 
            Alignment::fill_left      = fill_left             ;
            Alignment::fill_left_len  = fill_left_len         ; 
            Alignment::fill_right     = fill_right            ;
            Alignment::fill_right_len = fill_right_len        ;

            //input the return based on the last index the parser was at
            return p.k;

        }else if(id == PRINT_BIN) {
            Printing::printing = Printing::BIN;
            return k + strlen_tk(cmd) - 1;
        }else if(id == PRINT_HEX) {
            Printing::printing = Printing::HEX;
            return k + strlen_tk(cmd) - 1;
        }

        println("ERROR in ",__PRETTY_FUNCTION__,", forgot to input return index for ID:",id);
        return k - 1;
    }
}


// template<typename... Args> void println(int input, const char* str, Args... other) {
//     PrintCmds::printcmd(input, str);
//     println(other...);
// }

template<typename T, typename... Args> void println(const T& input, const Args&... other) {
    std::cout<<input;
    println(other...);
}

void print(){}

template<typename T> void print(const T& input) {
    std::cout<<input;
}


template<typename T, typename... Args> void print(const T& input, const char* str, const Args&... other) {
    PrintCmds::printcmd(input, str);
    print(other...);
}

template<typename T, typename... Args> void print(const T& input, const Args&... other) {
    std::cout<<input;
    print(other...);
}


//print int8_t and uint8_t as numbers instead of regular characters
void print(uint8_t c) {print((uint16_t)(c));}
void print(int8_t  c) {print((int16_t )(c));}
template<typename... Args> void print(uint8_t c, const Args&... other)   {print((uint16_t)(c)); print(other...);}
template<typename... Args> void print(int8_t  c, const Args&... other)   {print((int16_t)(c));  print(other...);}
void println(uint8_t c) {println((uint16_t)(c));}
void println(int8_t  c) {println((int16_t )(c));}
template<typename... Args> void println(uint8_t c, const Args&... other) {print((uint16_t)(c)); println(other...);}
template<typename... Args> void println(int8_t  c, const Args&... other) {print((int16_t)(c));  println(other...);}

//print Parser::Arg as a normal string
void print(const char* str, Parser::Arg arg)                                                    {printlen(str + arg.i, arg.len);                   }
template<typename... Args> void print(const char* str, Parser::Arg arg, const Args&... other)   {printlen(str + arg.i, arg.len); print(other...);  }
void println(const char* str, Parser::Arg arg)                                                  {printlen(str + arg.i, arg.len); println();        }
template<typename... Args> void println(const char* str, Parser::Arg arg, const Args&... other) {printlen(str + arg.i, arg.len); println(other...);}

void print(char* str, Parser::Arg arg)                                                    {print((const char*)(str), arg);  }
template<typename... Args> void print(char* str, Parser::Arg arg, const Args&... other)   {print((const char*)(str), arg, other...);  }
void println(char* str, Parser::Arg arg)                                                  {println((const char*)(str), arg);}
template<typename... Args> void println(char* str, Parser::Arg arg, const Args&... other) {println((const char*)(str), arg, other...);}

void print(Parser::Arg arg)                                                    {print  ("{",arg.i,", ",arg.len,"}");          }
template<typename... Args> void print(Parser::Arg arg, const Args&... other)   {print  ("{",arg.i,", ",arg.len,"}", other...);}
void println(Parser::Arg arg)                                                  {println("{",arg.i,", ",arg.len,"}");          }
template<typename... Args> void println(Parser::Arg arg, const Args&... other) {println("{",arg.i,", ",arg.len,"}", other...);}


//stuff to print the type
template<typename T>
#define get_t get_type_name //make short alias for function
std::string get_type_name(LINE_TRACKER) {
    #if SUPPORTS_PRETTY_FUNC
        //__PRETTY_FUNCTION__ looks like this : 
        //void print_type() [with T = Text_t]

        //get functions signature and what we are searching for
        const char* function_signature = __PRETTY_FUNCTION__;
        const char* search_start = "with T = ";
        const char* search_end   = ";";

        int start = findstr(function_signature, search_start)     ; start += strlen_tk(search_start);
        int end   = findstr(function_signature, search_end, start); end--;

        std::string str = "";
        for(int i = start; i <= end; i++) {
            str.push_back(function_signature[i]);
        }

        return str;
    #endif
}

template<typename T>
void print_type() {
    print(get_type_name<T>());
}


template<typename T>
void println_type() {
    print_type<T>();
    println();
}


template<typename T>
typename enable_if<!is_pointer<T>::value, int>::type
getBinNumLen(T n)
{
    int l = 0;
    if(n < 0) {
        n = -n;
        l++;
    }

    for(int i = sizeof(T) * 8 - 1; i >= 0; i--)
    {
        l++;

        if(i % 8 == 0) {
            l++;
        }
    }

    return l;
}


//enable only if is not a pointer
template<typename T>
typename enable_if<is_pointer<T>::value, int>::type
getBinNumLen(T ptr)
{
    return getBinNumLen((uintptr_t)(ptr));
}


template<typename T>
typename enable_if<!is_pointer<T>::value, int>::type
getHexNumLen(T n)
{
    int l = 0;


    //print the raw bits of the number as hex
    l+=2;
    for(int i = sizeof(T) * 8 - 4; i >= 0; i -= 4) {
        l++;
    }

    return l;
}


//enable only IF IT IS A POINTER
template<typename T>
typename enable_if<is_pointer<T>::value, int>::type
getHexNumLen(T ptr)
{
    return getHexNumLen((uintptr_t)(ptr));
}


//make a type to always fit the thing
template<size_t Size>
class fitsize_t {
    using type = choose_type<Size == 1, uint8_t, choose_type<Size == 2, uint16_t, choose_type<Size == 4, uint32_t, choose_type<Size == 8, uint64_t, void>>>>;
};


template<typename T>
typename enable_if<is_number<T>::value, void>::type
printbin(T n)
{
    if(n < 0) {
        n = -n;
        print("-");
    }

    for(int i = sizeof(T) * 8 - 1; i >= 0; i--)
    {
        print((n & (1ULL << (unsigned long long)(i))) >> i);

        if(i > 0 && i % 8 == 0) {
            print(" ");
        }
    }
}

template<typename T>
typename enable_if<is_pointer<T>::value, void>::type
printbin(T ptr)
{
    //print as a pointer instead
    printbin((uintptr_t)(ptr));
}


template<typename T>
typename enable_if<!is_number<T>::value && !is_pointer<T>::value, void>::type
printbin(T n)
{
    print(n);
}

template<typename T>
void printlnbin(T input)
{
    printbin(input);
    println();
}

// const char hex_numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const char hex_numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

template<typename T>
typename enable_if<is_number<T>::value, void>::type
printhex(T n)
{
    //invert number and print "-" in front
    if(n < 0) {
        n = -n;
        print("-");
    }

    //print the raw bits of the number as hex
    for(int i = sizeof(T) * 8 - 4; i >= 0; i -= 4) {
        print(hex_numbers[(n & (0b1111ULL << (unsigned long long)(i))) >> i]);
    }
}

template<typename T>
typename enable_if<is_pointer<T>::value, void>::type
printhex(T ptr) {
    //print the pointer value instead
    printhex((uintptr_t)(ptr));
}

void printhex(const char* str, bool prefix = 1) {
    const int str_len = strlen_tk(str);
    for(int i = 0; i < str_len; i++) {
        if(prefix && i != 0) print(' '); 
        if(prefix) print("0x");
        printhex((uint8_t)(str[i]));
    }
}

template<typename T>
typename enable_if<!is_number<T>::value && !is_pointer<T>::value, void>::type
printhex(T n) {
    print(n);
}

template<typename T>
void printlnhex(T input)
{
    printhex(input);
    println();
}

template<typename T>
void printarray_h(T array, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        println("[", PADR(3, std::to_string(i) + "]")," = ",array[i]);
    }
}

template<typename T>
void printarray_h(T array, size_t size, const char* inBetween)
{
    if(size > 0)
    {
        print(array[0]);
    }
    
    for(size_t i = 1; i < size; i++)
    {
        print(inBetween);
        print(array[i]);
    }
}

template<typename T>
typename enable_if<is_number<typename remove_pointers<T>::type>::value, void>::type 
printhexarray_h(T array, int size, const char* inBetween = 0) {
    if(inBetween != 0) {
        for(int i = 0; i < size; i++) {
            if(i != 0) {
                print(inBetween);
            }

            printhex(array[i]);
        }
    }else {
        for(int i = 0; i < size; i++) {
            print("[");
            print(i);
            print("] = ");
            printhex(array[i]);
            println();
        }
    }
}

template<typename T>
typename enable_if<is_number<typename remove_pointers<T>::type>::value, void>::type 
printbinarray_h(T array, int size, const char* inBetween = 0) {
    if(inBetween != 0) {
        for(int i = 0; i < size; i++) {
            if(i != 0) {
                print(inBetween);
            }

            printbin(array[i]);
        }
    }else {
        for(int i = 0; i < size; i++) {
            print("[");
            print(i);
            print("] = ");
            printbin(array[i]);
            println();
        }
    }
}



void printlen(const char* str, int64_t len, LINE_TRACKER_SHELL)
{
    if(len < 0) {
        println(ERROR_LINE,"negative length was inputed in the print len function");
        while(true) delay(1000);
        throw 1;
    } 

    for(int i = 0; i < len; i++)
    {
        print(str[i]);
    }
}
void printlnlen(const char* str, int64_t len, LINE_TRACKER)
{
    printlen(str, len, FND(), line, file);
    println();
}

//the holy grail of printing functions
template <typename T>
void debugHelper(int index, const char* funcInput, const T& input)
{
    //find the next comma (or the end char)
    while(funcInput[index] != ',' && funcInput[index] != '\0')
    {
        if(funcInput[index] == ' ')
        {
            index++;
            continue;
        }
        print(funcInput[index]);
        index++;
    }
    
    print(" = ");
    println(input);
    
    index++;
}

void debugHelper(int index, const char* funcInput, const char* input)
{
    //find the next comma (or the end char)
    while(funcInput[index] != ',' && funcInput[index] != '\0')
    {
        if(funcInput[index] == ' ')
        {
            index++;
            continue;
        }
        print(funcInput[index]);
        index++;
    }
    
    print(" = \"");
    print(input);
    print("\"");
    println();

    index++;
}

void debugHelper(int index, const char* funcInput, char input)
{
    //find the next comma (or the end char)
    while(funcInput[index] != ',' && funcInput[index] != '\0')
    {
        if(funcInput[index] == ' ')
        {
            index++;
            continue;
        }
        print(funcInput[index]);
        index++;
    }
    
    print(" = '");
    switch(input) {
        case '\a' : print("\\a"); break;
        case '\b' : print("\\b"); break;
        case '\f' : print("\\f"); break;
        case '\r' : print("\\r"); break;
        case '\v' : print("\\v"); break;
        case '\'' : print("\\'"); break;
        case '\?' : print("\\?"); break;
        default   : print(input); break;
    }
    print("'");
    println();

    index++;
}

void debugHelper(int index, const char* funcInput, char* input) {
    debugHelper(index, funcInput, (const char*)(input));
}

void debugHelper(int index, const char* funcInput, std::string& input) {
    debugHelper(index, funcInput, input.c_str());
}

template <typename... Args>
void debugHelper(int index, const char* funcInput, char input, const Args&... other) {
    //find the next comma (or the end char)
    while(funcInput[index] != ',' && funcInput[index] != '\0')
    {
        if(funcInput[index] == ' ')
        {
            index++;
            continue;
        }
        print(funcInput[index]);
        index++;
    }
    
    print(" = \'");
    switch(input) {
        case '\a' : print("\\a"); break;
        case '\b' : print("\\b"); break;
        case '\f' : print("\\f"); break;
        case '\r' : print("\\r"); break;
        case '\v' : print("\\v"); break;
        case '\'' : print("\\'"); break;
        case '\?' : print("\\?"); break;
        default   : print(input); break;
    }
    print("\'\n");
    
    //skip the comma for next variable
    index++;
    
    debugHelper(index, funcInput, other...);
}

template <typename... Args>
void debugHelper(int index, const char* funcInput, const char* input, const Args&... other) {
    //find the next comma (or the end char)
    while(funcInput[index] != ',' && funcInput[index] != '\0')
    {
        if(funcInput[index] == ' ')
        {
            index++;
            continue;
        }
        print(funcInput[index]);
        index++;
    }
    
    print(" = \"");
    print(input);
    print("\"\n");
    
    //skip the comma for next variable
    index++;
    
    debugHelper(index, funcInput, other...);
}

template <typename... Args>
void debugHelper(int index, const char* funcInput, char* input, const Args&... other) {
    debugHelper(index, funcInput, (const char*)(input), other...);
}

template <typename... Args>
void debugHelper(int index, const char* funcInput, std::string input, const Args&... other) {
    debugHelper(index, funcInput, input.c_str(), other...);
}


template <typename T, typename... Args>
void debugHelper(int index, const char* funcInput, const T& input, const Args&... other)
{
    //find the next comma (or the end char)
    while(funcInput[index] != ',' && funcInput[index] != '\0')
    {
        if(funcInput[index] == ' ')
        {
            index++;
            continue;
        }
        print(funcInput[index]);
        index++;
    }
    
    print(" = ");
    print(input);
    print("\n");
    
    //skip the comma for next variable
    index++;
    
    debugHelper(index, funcInput, other...);
}



template<typename T>
typename enable_if<!is_pointer<T>::value, int>::type
getLen(T num) {
    int len = 0;

    //if negative add one to length ('-' char at the start)
    if(num < 0) {
        num = -num;
        len++;
    }

    //do at least once (0 takes one character), count the number of /10 you can do before you reach 0
    do
    {
        num /= 10;
        len++;
    } while(num != 0);

    return len;
}

int getLen(std::string str) {
    return str.length();
}

int getLen(const char* str) {
    return strlen_tk(str);
}

int getLen(double d) {
    return 0;//idk length of double
}

int percentageBarNumberOfDotsForTheLoadingBar = 0;
long long lastShownPercentageBar = 0;
void percentageBar(long long start, long long index, long long end, int new_line_c = 20, long long precision = 100, int style = 2)
{

    //calculate total to go through
    long long total = end - start + 1;

    long long reducedPrecision = precision;

    double percentage = -1;

    //check for error with modulo by zero because of poor precision
    if(total < precision){reducedPrecision = total;}
    if(((index - start) % (total / reducedPrecision)) != 0ULL && !(index == end)){return;}


    if(!(index == end))
    {
        //calculate percentage
        percentage = (double)index * (double)precision / (double)total;
    }else
    {
        //make satisfying 100% at the end
        percentage = 100;
    }

    for(int i = 0; i < new_line_c; i++)
    {
        println();
    }

    if(style == 0)
    {
        

        for(int i = 0; i < 100; i++)
        {
            print("=");
        }

        println();

        for(int i = 0; i < (int)percentage * 100 / precision; i++)
        {
            print("#");
        }
        
        println();

        for(int i = 0; i < 100; i++)
        {
            print("=");
        }

        println();

        // Setup at the start
        std::cout.setf(std::ios::fixed, std::ios::floatfield);
        std::cout.precision(2);

        if(precision == 100)
        {
            println(percentage,"%");
        }else
        {
            println(percentage," / ",precision);
        }

        // This removes the "fixed" requirement and returns to "defaultfloat" behavior
        std::cout.unsetf(std::ios::fixed);
    }else if(style == 1)
    {

        print("[");

        for(int i = 0; i < (int)percentage * 100 / precision; i++)
        {
            print("#");
        }

        for(int i = (int)percentage * 100 / precision; i < 100; i++)
        {
            print("-");
        }

        print("] ");

        // Setup at the start
        std::cout.setf(std::ios::fixed, std::ios::floatfield);
        std::cout.precision(2);

        if(precision == 100)
        {
            print(percentage,"%       ");
        }else
        {
            print(percentage," / ",precision,"       ");
        }

        println();

        std::cout << std::flush;
    
        // This removes the "fixed" requirement and returns to "defaultfloat" behavior
        std::cout.unsetf(std::ios::fixed);
    }else if(style == 2)
    {

        print("Loading");

        if(millis() - lastShownPercentageBar >= 500)
        {
            lastShownPercentageBar = millis();

            percentageBarNumberOfDotsForTheLoadingBar += 1;

            percentageBarNumberOfDotsForTheLoadingBar = percentageBarNumberOfDotsForTheLoadingBar % 4;
        }

        for(int i = 0; i < percentageBarNumberOfDotsForTheLoadingBar; i++)
        {
            print(".");
        }

        println();

        //println(" ̲̅=̲̅=̲̅=̲̅=̲̅=̲̅=̲̅=̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅ ̲̅  ");

        // // print underline
        // println("\xCC\xB2");

        // // print overline
        // println("\xCC\x85");

        for(int i = 0; i < (int)percentage * 40 / precision; i++)
        {
            // print underline
            print("\xCC\xB2");

            // print overline
            print("\xCC\x85");
            
            print("=");
        }

        for(int i = (int)percentage * 40 / precision; i < 40; i++)
        {
            // print underline
            print("\xCC\xB2");

            // print overline
            print("\xCC\x85");

            print(" ");
        }
        
        print("   ");

        // Setup at the start
        std::cout.setf(std::ios::fixed, std::ios::floatfield);
        std::cout.precision(2);

        if(precision == 100)
        {
            print(percentage,"%       ");
        }else
        {
            print(percentage," / ",precision,"       ");
        }

        println();

        std::cout << std::flush;
    
        // This removes the "fixed" requirement and returns to "defaultfloat" behavior
        std::cout.unsetf(std::ios::fixed);
    }

} 

void debug_banner_h()
{
    ::println("===========[DEBUGGING]===========");
}

template<typename... Args>
void debug_banner_h(Args... args)
{
    ::println("===========[",args...,"]===========");
}

void debug_bound_h(int len, int i, LINE_TRACKER_SHELL) {
    if(i < 0 || len <= i) {
        println(ERROR_LINE,"out of bounds array access");
    }
}

long long powi(long long base, long long exp) {
    long long res = 1;
    for (long long i = 0; i < exp; i++) res *= base;
    return res;
}

//function for random in between
uint32_t seed = 1;
#define SEED_MAX ((1ULL << (sizeof(seed) * 8)) - 1)
long random(long s, long e)
{

    //apply the magic "randomizer" algorithm 10 times just to really randomize it
    for(int i = 0; i < 10; i++) {
        seed ^= seed << 13;
        seed ^= seed >> 17;
        seed ^= seed << 5;
    }
    
    /*
    how to reduce the seed to a single number between designated range
    - first you divide it by the number of possible numbers you want (range)
    - then you floor the number (or just use integer division for previous step as it does the flooring automatically)
    - then you add the start number to that 
    
    flawless strategie
    */
    
    //get the range
    long long range = (long long)(e) - (long long)(s) + 1LL;

    //Return the random number
    return seed * range / (SEED_MAX + 1) + s;
}


unsigned long long factorial(int num)
{
    unsigned long long output = 1;

    for(int i = num; i > 0; i--)
    {
        output *= i;
    }

    return output;
}
bool strcmp1(const char* s1, const char* s2)
{
    while((*s1 == *s2))
    {
        s1++;
        s2++;

        if(!(bool)(*s1))
        { 
            return true;
        }
    }

    return false;
}

long long strlen_tk(const char* str) {
    unsigned int length = 0;
    
    // Loop through the string until the character at index 'length' is \0
    while (str[length] != '\0') {
        length++;
    }
    
    return length;
}

//does same thing as regular strcmp (toolkit version)
int strcmp_tk(const char *s1, const char *s2) {
    //while not at the end of string 1 and while both characters are equal, increase character index
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    // Return the difference in ASCII values
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}    
int strcmp_tk(const char* str1, const char* str2, unsigned int len1, unsigned int len2 = UINT_MAX)
{

    //figure out the length of the corresponding string if not provided
    if(len1 == UINT_MAX)
    {
        len1 = 0;
        while(str1[len1] != '\0')
        {
            len1++;
        }
    }

    //figure out the length of the corresponding string if not provided
    if(len2 == UINT_MAX)
    {
        len2 = 0;
        while(str2[len2] != '\0')
        {
            len2++;
        }
    }

    int i = 0;                                               //store current index character
    for(;i < len1 && i < len2 && str1[i] == str2[i];i++);//go through the string until we either reach the end of one of the string or a character that doesn't match

    char c1 = (i < len1)?(str1[i]):('\0');                   //simulate end null char (we don't know if we have one)
    char c2 = (i < len2)?(str2[i]):('\0');                   //simulate end null char (we don't know if we have one)

    //return comparison between both characters
    return (uint8_t)(c1) - (uint8_t)(c2);
}
int strcmp_tk(const char* orig1, Parser::Arg str1, const char* orig2, Parser::Arg str2) {
    return strcmp_tk(orig1 + str1.i, orig2 + str2.i, str1.len, str2.len);
}
int strcmp_tk(std::string orig1, Parser::Arg str1, const char* orig2, Parser::Arg str2) {
    return strcmp_tk(orig1.c_str() + str1.i, orig2 + str2.i, str1.len, str2.len);
}
int strcmp_tk(const char* str1, unsigned int len1, const char* orig2, Parser::Arg str2) {
    return strcmp_tk(str1, orig2 + str2.i, len1, str2.len);
}
int strcmp_tk(const char* str1, unsigned int len1, std::string orig2, Parser::Arg str2) {
    return strcmp_tk(str1, orig2.c_str() + str2.i, len1, str2.len);
}
int strcmp_tk(const char* str1, const char* orig2, Parser::Arg str2) {
    return strcmp_tk(str1, orig2 + str2.i, strlen_tk(str1), str2.len);
}
int strcmp_tk(const char* str1, std::string orig2, Parser::Arg str2) {
    return strcmp_tk(str1, orig2.c_str() + str2.i, strlen_tk(str1), str2.len);
}
int strcmp_tk(const char* orig1, Parser::Arg str1, const char* str2, unsigned int len2) {
    return strcmp_tk(orig1 + str1.i, str2, str1.len, len2);
}
int strcmp_tk(std::string orig1, Parser::Arg str1, const char* str2, unsigned int len2) {
    return strcmp_tk(orig1.c_str() + str1.i, str2, str1.len, len2);
}
int strcmp_tk(const char* orig1, Parser::Arg str1, const char* str2) {
    return strcmp_tk(orig1 + str1.i, str2, str1.len, strlen_tk(str2));
}
int strcmp_tk(std::string orig1, Parser::Arg str1, const char* str2) {
    return strcmp_tk(orig1.c_str() + str1.i, str2, str1.len, strlen_tk(str2));
}



double strToNum(const char* str, size_t len)
{
    //figure out the length of "str" (the string) if not already been done (if len equals SIZE_MAX)
    if(len == SIZE_MAX)
    {
        len = 0;
        while(str[len] != '\0')
        {
            len++;
        }
    }
    
    //index to go through the number
    unsigned int i = 0;
    int outputIndex = 0;
    int exponent = 0;
    bool dot = false;
    bool negative = 0;

    double num = 0;

    while(true)
    {
        // temp debug: println("-> '",str[i],"'");

        //skip all leading spaces or separators
        while(i < len && (str[i] == ' ' || str[i] == '\n' || str[i] == ',' || str[i] == '\''))
        {
            // temp debug: println("skipping");
            i++;
            // temp debug: println("-> '",str[i],"'");
        }

        if(i < len && outputIndex == 0 && str[i] == '-')
        {
            negative = 1;
            i++;
            continue;
        }

        //if we reached the end of the string get out of the loop
        if(i >= len)
        {
            // temp debug: println("getting out of loop");
            break;
        }

        //if we saw a dot (indicates decimal number we set dot to true)
        if(str[i] == '.')
        {
            // temp debug: println("saw dot, disabling exponent count");
            dot = true;
            i++;
            continue;
        }

        char c = str[i];
        int digit = 0;
        if('0' <= c && c <= '9')
        {
            digit = c - '0';//get the digit based on the nifty character trick
            // temp debug: println("saw digit, converted to ",digit);

        }else
        {
            //if its not a digit than throw an error and get out of the function
            // println("ERROR, strToNumber function failed, '",str,"' is not a number");
            // return NAN;
            break;
        }

        
        num += digit * pow(10, -outputIndex);
        // temp debug: println("added ",digit * pow(10, -outputIndex)," to number : ",num);

        outputIndex++;
        i++;
        if(dot == false)
        {
            exponent++;
            // test print println("increased exponent : ",exponent);
        }
    }

    return (1 - 2 * negative) * num * powi(10, exponent - 1);
}
double strToNum(const char* orig, Parser::Arg str) {
    return strToNum(orig + str.i, str.len);
}

template<typename Lambda>
double strMath(const char* str, int len, Lambda extraWords)
{

    //figure out the length if it wasn't provided in the input (if len was equal to -1)
    if(len == -1)
    {
        len = 0;
        while(str[len] != '\0')
        {
            len++;
        }

        // println("length is ",len);
    }
    
    const char signs[9]          = {'^','*','/','%','+','-'};
    const unsigned char order[9] = { 0 , 1 , 1 , 1 , 2 , 2 };

    //ignore spaces and parenthesis incompassing the whole string
    while(true)
    {
        //get rid of spaces at the front
        if(str[0] == ' ')
        {
            str += 1;
            len -= 1;

        //get rid of spaces at the end
        }else if(str[len - 1] == ' ')
        {
            len -= 1;
            
        //get rid of any parenthesis encompassion the whole string
        }else if(str[0] == '(' && str[len - 1] == ')')
        {

            //check if those parenthesis actually "connect" 
            int parenthesisLevel = 0;
            for(int i = 0; i < len; i++)
            {
                if(str[i] == '(')
                {
                    parenthesisLevel += 1;
                }else if(str[i] == ')')
                {
                    parenthesisLevel -= 1;
                }
                
                if(i == len - 1)
                {
                    //get rid of the thing
                    str += 1;
                    len -= 2;

                    //set parenthesisLevel to 1 to stop it from going out of the loop
                    parenthesisLevel = 1;
                    break;
                }

                if(parenthesisLevel <= 0)
                {
                    break;
                }
            }

            //parenthesisLevel is set to zero if we found inside of the string a parenthesis below or equal to zero
            if(parenthesisLevel == 0)
            {
                //go outside of the loop
                break;
            }
        }else
        {
            //if none of the stuff was done, then get out of the loop
            break;
        }
    }

    // print("str math -> '");
    // for(int i = 0; i < len; i++)
    // {
    //     print(str[i]);
    // }
    // println("'");

    //make a variable to remember if we ever found a operator (if we didn't then its probably just a normal number)
    bool foundAnySigns = false;

    //go through all possible order values 0-255
    for(int i = 255; i >= 0; i--)
    { 
        //start out default at parenthesis level 0, increase when ")", decrease when "("
        int parenthesisLevel = 0;

        //go through all of the string BACKWARDS checking to find a sign with order "i"
        for(int j = len - 1; j >= 0; j--)
        {
            if(str[j] == ')')
            {
                parenthesisLevel += 1;
            }else if(str[j] == '(')
            {
                parenthesisLevel -= 1;
            }

            if(parenthesisLevel == 0)
            {
                //go through all of the signs with that order (order "i")
                for(int k = 0; k < (int)(sizeofarray(order)); k++)
                {
                    //this plays for all signs that have order "i"
                    if(order[k] == i)
                    {

                        //if the str character at index "j" is the same as the sign character indexed by "k" inside of the signs array
                        if(str[j] == signs[k])
                        {
                            //found the last operation to do at index "j" of str!!!


                            bool success = false;
                            {
                                //go back from the point where we found the symbol
                                int l = j - 1;
                                while(0 <= l)
                                {
                                    //if we find something that is not a space or a sign then we found the number in between and its good, but if we hit a sign first then its a fail
                                    if(str[l] != ' ')
                                    {
                                        success = true;

                                        for(int n = 0; n < (int)(sizeofarray(signs)); n++)
                                        {
                                            if(str[l] == signs[n])
                                            {
                                                success = false;
                                                break;
                                            }
                                        }

                                        break;
                                    }

                                    l--;
                                }
                            }

                            //if we didn't find any number in between both signs then we forget about this
                            if(success == false)
                            {
                                // code works without error (error is useless) *I BELIEVE, BUT AINT SURE
                                // println("didn't find any number to the left of index : ",j);
                                // display_info(str, j);
                                break;
                            }


                            //if we have nothing to the left its probably a negative number so skip it
                            if(j == 0 && str[j] == '-')
                            {
                                return -strMath(str + j + 1, len - j - 1, extraWords);
                            }

                            // do strMath for the left and right part of the operation
                            double left = strMath(str, j, extraWords);
                            double right = strMath(str + j + 1, len - j - 1, extraWords);
                            double result = 0;

                            //IMPORTANT NOTE : EXCEPTION FOR NEGATIVE NUMBER, IF THERE ISN'T ANYTHING TO THE LEFT OF THE NUMBER THEN WE DO THE WEIRD NINJUTS BULLSHIT NEGATIVE NUMBER!!!!

                            //do the right mathematical operation based on what str[j] is equal
                            if      (str[j] == '+')
                            {
                                // print("doing : ",left," + ",right," = ");
                                result = left + right;
                                // println(result);
                            }else if(str[j] == '-')
                            {
                                // print("doing : ",left," - ",right," = ");
                                result = left - right;
                                // println(result);
                            }else if(str[j] == '*')
                            {
                                // print("doing : ",left," * ",right," = ");
                                result = left * right;
                                // println(result);
                            }else if(str[j] == '/')
                            {
                                // print("doing : ",left," / ",right," = ");
                                result = left / right;
                                // println(result);
                            }else if(str[j] == '%')
                            {
                                // print("doing : ",left," % ",right," = ");
                                result = fmod(left, right);
                                // println(result);
                            }else if(str[j] == '^')
                            {
                                // print("doing : ",left," ^ ",right," = ");
                                result = pow(left, right);
                                // println(result);
                            }
                            
                            return result;
                        } 
                    }
                }
            } 
        }
    }

    //if we didn't find any signs then its probably just a number (check len bigger than zero to make sure we aren't working with a empty string)
    if(len > 0 && foundAnySigns == false)
    {
        //check before sending to strToNum function if it has any non number characters
        for(int i = 0; i < len; i++)
        {

        //if its not a number
        if((str[i] < '0' || '9' < str[i]) && str[i] != '-' && str[i] != ' ' && str[i] != '.')
        {
            

            //this part also catches function, implement algorithm to catch "sqrt(...)" function, get what the insides of the function equal to and perform sqrt on the insides
            int j = 0;
            while(j < len)
            {
                if(ISLETTER(str[j]))
                {
                    int start = j;
                    while(str[j] != '(' && j < len)
                    {
                        j++;
                    }

                    //did not find a parenthesis for the function
                    if(j >= len) {
                        break;
                    }

                    int end = j - 1;

                    j++;//incraese one more so that it starts inside of the parenthesis

                    int fnLen = end - start + 1;
                    const char* fnStr = str + start;
                    
                    while(fnStr[0] == ' ')
                    {
                        fnStr += 1;
                    }

                    while(fnStr[fnLen - 1] == ' ')
                    {
                        fnLen -= 1;
                    }

                    // print("fn name is \"");
                    // printlen(fnStr, fnLen);
                    // println("\"");

                    {

                        int j = start + fnLen + 1; 
                        
                        start = j;
                        
                        int nofparenthesis = 1;
                        while(nofparenthesis >= 1 && j < len)
                        {
                            
                            if(str[j] == '(')
                            {
                                nofparenthesis += 1;
                            }else if(str[j] == ')')
                            {
                                nofparenthesis -= 1;
                            }

                            j++;
                        }
                        j--;

                        end = j - 1;

                        int inputLen = end - start + 1;
                        const char* inputStr = str + start;
                    
                        // print("fn input is \"");
                        // printlen(inputStr, inputLen);
                        // println("\", doing string math on it");

                        if      (strcmp_tk(fnStr, "sqrt", fnLen) == 0)
                        {
                            double fnInput = strMath(inputStr, inputLen, extraWords);
                            double result  = sqrt(fnInput);
                            // println("doing : sqrt(",fnInput,") = ",result);
                            return result;
                        }else if(strcmp_tk(fnStr, "sin" , fnLen) == 0)
                        {
                            double fnInput = strMath(inputStr, inputLen, extraWords);
                            double result  = sin(fnInput);
                            // println("doing : sin(",fnInput,") = ",result);
                            return result;
                        }else if(strcmp_tk(fnStr, "tan" , fnLen) == 0)
                        {
                            double fnInput = strMath(inputStr, inputLen, extraWords);
                            double result  = tan(fnInput);
                            // println("doing : sin(",fnInput,") = ",result);
                            return result;
                        }else if(strcmp_tk(fnStr, "cos" , fnLen) == 0)
                        {
                            double fnInput = strMath(inputStr, inputLen, extraWords);
                            double result  = cos(fnInput);
                            // println("doing : sin(",fnInput,") = ",result);
                            return result;
                        }

                    }
                }

                j++;
            }

            return extraWords(str, len);

            return NAN;
        }
        }

        return strToNum(str, len);
    }


    println("unknown math : didn't fin anything");
    return NAN;
}

double strMath(const char* str, int len)
{
    auto empty_lambda = [](const char* str, int len) -> double 
    {
        //check if pi
        if(strcmp_tk(str, "pi", len) == 0) {
            return 3.1415926535897932384626433832795028841971693993751;//return pi
        }

        print("unknown math expression : \"");
        printlen(str, len);
        print("\"");
        println();
        return NAN;
    };

    return strMath(str, len, empty_lambda);
}

//============= CUSTOM CLASS TO STORE LAMBDAS =============// 
#if true

template<typename Return, typename... Args>
class BaseCallable
{
    public:

    //virtual call command (this is so the compiler remembers that call exists so it can call LambdaCallable's call function without having to deal with the custom Lambda)
    virtual Return call(Args... args) = 0;

    //virtual clone function (so calls the LambdaCallable clone function to clone the LambdaCallable)
    virtual BaseCallable* clone() = 0;
    
    //virtual destructor because we want the destructor to destruct idk
    virtual ~BaseCallable(){}
};

template<typename Lambda, typename Return, typename... Args>
class LambdaCallable : public BaseCallable<Return, Args...>
{
    public:

    //store the lambda
    Lambda lambda;

    //clone function to (clones the lamdba too)
    LambdaCallable* clone()
    {
        return new LambdaCallable<Lambda, Return, Args...>(lambda);
    }

    //link call function with the actuall lambda
    Return call(Args... args)
    {
        //call operator()() with specified args and return specified Return type
        return lambda(args...);
    }

    //constructor that copies the to lambda
    LambdaCallable(const Lambda& lambda) : lambda(lambda) // copy constructor (COPY lambda to LambdaCallable::lambda variable)
    {

    }
};

//super sofisticated line tracker to track lines even for operator= one argument thing
template<typename T>
struct LineTracker
{
    T value;
    int line;
    const char* file;
    
    //constructor that translates any type into a line tracker but secretly also stores the line and files
    LineTracker(T input, int line1 = __builtin_LINE(), const char* file1 = __builtin_FILE()) :
    value(input),
    line(line1),
    file(file1)
    {}
};

struct Tracker {
    int line;
    const char* file;

    Tracker(int l = __builtin_LINE(), const char* f = __builtin_FILE()) : 
    line(l),
    file(f)
    {}

    void debug() {
        DEBUG(line, file);
    }
};

template<typename Return, typename... Args>
class Function
{
    public:

    //this type is literally just here for the line number
    struct AVerySpecificTypeForAVerySpecificProblem{};

    //variable that points to a LambdaCallable disguised as a BaseCallable because we can't set the type of the lambda at compile time
    BaseCallable<Return, Args...>* lambdaCallable = nullptr;

    //std::is_same<A, B>
    //std::enable_if<condition, type>

    //weird structs that check compile time if its a function so that it doesn't accidentally choose a function
    template<typename T>
    struct is_Function
    {
        //create a static const variable to be able to index with :: (bcs static = only one in memory so can index easly idk)
        static const bool value = false;
    };

    //specific template if its a Function type with any Return type and any arguments I guess
    template <typename R, typename... A>
    struct is_Function<Function<R, A...>>
    {
        //static const variable to easly index when using it I guess
        static const bool value = true;
    };

    template<typename... Other> 
    Function(Other... other) {
        DEBUG_BANNER();
        DEBUG(__PRETTY_FUNCTION__);
    }

    //Function constructor that sets the lambda but not a Function
    template<typename Lambda> //second typename has no name and default argument is either set to void or not set depening on compile time computed types
    Function(const Lambda& lambda, typename enable_if<!is_Function<Lambda>::value && !is_fn<Lambda>::value, void>::type* = nullptr)
    {
        //dynamic memory allocation for a LambdaCallable object that we are going to store disguised as a BaseCallable to be able to call it
        lambdaCallable = new LambdaCallable<Lambda, Return, Args...>(lambda);
    }

    
    //constructor for functions that don't have the same template as this Function class
    template<typename Lambda>
    Function(const Lambda& function, typename enable_if<is_Function<Lambda>::value && !is_fn<Lambda>::value, void>::type* = nullptr, LINE_TRACKER)
    {
        println(ERROR_LINE,"tried setting a Function class to another Function class with different Return type or Arguments");
    }

    //Function constructor to copy another Function with same template
    Function(const Function<Return, Args...>& function)
    {
        //if we are copying ourself, shouldn't happen because constructor but who knows, we don't do anything
        if(this == &function) return;

        //if the function we are copying has a lambdaCallable associated with it
        if(function)
        {
            //set lambdaCallable to a clone of the lambdaCallable of the function
            lambdaCallable = function.lambdaCallable->clone();
        }
    }

    Function(Return(*raw_fn)(Args...)) {
        lambdaCallable = new LambdaCallable<Return(*)(Args...), Return, Args...>(raw_fn);
    }

    //Function constructor (same as default constructor, for nullptr)
    Function(void* ptr)
    {
        if(ptr != nullptr)
        {
            println("ERROR line ",__LINE__,", function was set to a pointer other than nullptr, this is not supposed to happen (this constructor might be running instead of another correct one)");
        }
    }

    //default function constructor if you wish to set the lambda afterwards
    Function(){}

    void operator=(Return(*raw_fn)(Args...)) {
        //delete this current lambda (we are going to replace it)
        if(lambdaCallable != nullptr)
        {
            //remove lambdaCallable from memory
            delete lambdaCallable;

            //set lambdaCallable to nullptr (the function we are copying might not have a lambda associated with it, in that case we are essentially copying an empty function and so its important we set the pointer to nullptr so the code knows that this lambdaCallable isn't linked yet)
            lambdaCallable = nullptr;
        }

        //if the function we are copying has a lambdaCallable associated with it
        if(raw_fn != nullptr)
        {
            //set the lambdaCallable to the raw function pointer
            lambdaCallable = new LambdaCallable<Return(*)(Args...), Return, Args...>(raw_fn);
        }
    }

    //set a new lambda (ONLY IF ITS A FUNCTION)
    template<typename Lambda>
    typename enable_if<!is_Function<Lambda>::value && !is_fn<Lambda>::value, void>::type //if its a function we set a type, if its not we set a weird type that doesn't work so C++ compiler leaves us the heck alone
    operator=(const Lambda& lambda)
    {
        //destroy the previous lambda pointer storage variable (if available and not nullptr)
        if(lambdaCallable != nullptr)
        {
            delete lambdaCallable;
        }

        //dynamic memory allocation for a new LambdaCallable object
        lambdaCallable = new LambdaCallable<Lambda, Return, Args...>(lambda);
    }

    //give out error because trying to set Function to another Function with different arguements / return type
    template<typename Lambda>
    typename enable_if<is_Function<Lambda>::value && !is_fn<Lambda>::value, void>::type //if its a function we set a type, if its not we set a weird type that doesn't work so C++ compiler leaves us the heck alone
    operator=(LineTracker<Lambda> function)
    {
        println("ERROR line ",function.line," in ",function.file,", tried setting a Function class to another Function class with different Return type or Arguments");
    }

    //copy another Function with same template
    void operator=(const Function<Return, Args...>& function)
    {
        //if we are copying ourself, shouldn't happen because constructor but who knows, we don't do anything
        if(this == &function) return;
    
        //delete this current lambda (we are going to replace it)
        if(lambdaCallable != nullptr)
        {
            //remove lambdaCallable from memory
            delete lambdaCallable;

            //set lambdaCallable to nullptr (the function we are copying might not have a lambda associated with it, in that case we are essentially copying an empty function and so its important we set the pointer to nullptr so the code knows that this lambdaCallable isn't linked yet)
            lambdaCallable = nullptr;
        }

        //if the function we are copying has a lambdaCallable associated with it
        if(function)
        {
            //set lambdaCallable to a clone of the lambdaCallable of the function
            lambdaCallable = function.lambdaCallable->clone();
        }
    }

    //this is to play the function, does lineTracker on every element
    template<typename Dummy = void, typename = typename enable_if<sizeof...(Args) >= 1 && is_same<Dummy, void>::value, void>::type>
    Return operator()(LineTracker<Args>... args)
    {
        if(lambdaCallable == nullptr)
        {
            int line = 0;
            const char* file = nullptr;

            //expand the args pack and set the line to the first packs
            int dummy[] = 
            {
                (
                    //set line and file to the recorded line and file
                    (line = args.line, file = args.file), 

                    //then we set the number in the dummy array to zer anyways
                    0

                //expand args pack
                )...
            };


            /*
            
            
            
            (int)((line == ((int)0)) ? (line = args.LineTracker<T>::line), (file = args.LineTracker<T>::file) : ((int)0)), ((int)0)
            
            
            
            
            */

            //so we don't get unused dummy variaible warning
            (void)(dummy);

            println(ERROR_LINE,"the Function call with \"()\" was impossible because Function wasn't set to any lambdas        tip : to check if a Function has been set (to a lambda) just check if the object itself is true or false (EX: \"Function<void> fn; if(fn){/*function has been set*/}else{/*function was not set*/}\")");
            while(true);
        }

        return (*lambdaCallable).call(args.value...);
    }

    template<typename Dummy = void, typename = typename enable_if<sizeof...(Args) == 0 && is_same<Dummy, void>::value, void>::type>
    Return operator()(AVerySpecificTypeForAVerySpecificProblem dummy = {}, LINE_TRACKER)
    {
        if(lambdaCallable == nullptr)
        {
            println(ERROR_LINE,"the Function call with \"()\" was impossible because Function wasn't set to any lambdas        tip : to check if a Function has been set (to a lambda) just check if the object itself is true or false (EX: \"Function<void> fn; if(fn){/*function has been set*/}else{/*function was not set*/}\")");
            while(true);
        }

        return (*lambdaCallable).call();
    }
    
    //checking boolean value of this object will return if it has been assigned a lambda to or not (if the Function has been set)
    operator bool() const
    {
        //if lambdaCallable is a nullptr it means it hasn't been assigned to (so we check if isn't a nullptr)
        return lambdaCallable != nullptr;
    }

    //Destructor to destroy the dynamically allocated lambda pointer / call linker class
    virtual ~Function()
    {
        //if the lambda Callable exists, delete it
        if(lambdaCallable != nullptr)
        {
            //destroy the lambda pointer storage variable thingy because Function object is getting destroyed (would cause memory leaks if we didn't delete)
            delete lambdaCallable;
        }
    }
    
};

template<typename R, typename... A> bool operator==(Function<R, A...>& fn, decltype(nullptr)) {return !(bool)(fn);}
template<typename R, typename... A> bool operator==(decltype(nullptr), Function<R, A...>& fn) {return !(bool)(fn);}
template<typename R, typename... A> bool operator!=(Function<R, A...>& fn, decltype(nullptr)) {return  (bool)(fn);}
template<typename R, typename... A> bool operator!=(decltype(nullptr), Function<R, A...>& fn) {return  (bool)(fn);}

//also make the "std::function" equivalent work too
template<typename Return, typename... Args>
class Function<Return(Args...)> : public Function<Return, Args...> {
    using Function<Return, Args...>::Function;//use all constructors
};

#endif
//============= CUSTOM CLASS TO STORE LAMBDAS =============//

uint64_t total_time_taken_up = 0;
/**
 * @brief function to find text in other text with custom end characters
 * @param text the text you want to search in
 * @param find the text you want to find
 * @param find_i the index where you want to search at
 * @param custom_end input a normal string with all of the characters you want to include as safe ending characters, if it found the specific text and after it was a character in your list than its going to allow it, else not. set to nullptr to include all
 * @param exclude_end affects custom_end whether to exclude or include the custom strings (include meaning characters you put in custom string will be safe characters while exclude means that any character you put is unsafe)
 * @param custom_start input a normal string with all of the characters you want to include as safe starting characters, if it found the specific text and after it was a character in your list than its going to allow it, else not. set to nullptr to include all (defaults to including all)
 * @param exclude_start affects custom_start whether to exclude or include the custom strings (include meaning characters you put in custom string will be safe characters while exclude means that any character you put is unsafe)
 * @retval returns a boolean representing if the two strings are the same
 */
bool checkstr(const char* text, int text_len, const char* find, int find_len, int find_i, bool ignore_case, const char* custom_end, bool exclude_end, const char* custom_start, bool exclude_start)
{
    //check if we didn't specify the length of text or find
    if(text_len == -1) text_len = strlen_tk(text);
    if(find_len == -1) find_len = strlen_tk(find);

    //exclude if the start characters don't match
    if(custom_start == nullptr|| find_i <= 0 /* || find_i >= text_len */)
    {
        //do nothing
    }else
    {
        if(exclude_start)
        {
            //bound check, if we are currently at index 0 there is no point in searching one index before as there is no characters (we know its going to work)
            if((find_i - 1) >= 0)
            {
                int j = 0;
                while(custom_start[j] != '\0')
                {
                    //check if the thing right after the word is an allowed character
                    if(text[find_i - 1] == custom_start[j]) 
                    {
                        return false;
                    }
                    j++;
                }
            }

        }else
        {
            //bound check, if we are currently at index 0 there is no point in searching one index before as there is no characters (we know its going to work)
            if((find_i - 1) >= 0)
            {
                bool success = false;
                int j = 0;
                while(custom_start[j] != '\0')
                {
                    //check if the thing right after the word is an allowed character
                    if(text[find_i - 1] == custom_start[j]) 
                    {
                        success = true;
                        break;
                    }
                    j++;
                }
                
                //if we didn't succeed in finding any of the characters then return false checkstr failed
                if(!success)
                {
                    return false;                    
                }
            }
        }
    }

    //go through the find string because we want to find it inside of the bigger string (it only checks if its at the start)
    int i = 0;
    while(i < find_len)
    {
        //if the characters at the same index are not the same then the strings are not the same, return false
        if(ignore_case)
        {
            if(strcmp_tk(find, "rightarrow") == 0) println((char)UPPERCASE(text[find_i + i])," == ",(char)UPPERCASE(find[i]));
            if(UPPERCASE(text[find_i + i]) != UPPERCASE(find[i]))
            {
                return false;
            }
        }else
        {
            if(text[find_i + i] != find[i]) 
            {
                return false;
            }
        }

        i++;
    }

    if(custom_end == nullptr || find_i + i >= text_len)
    {
        return true;
    }else {
        if(exclude_end)
        {
            int j = 0;
            while(custom_end[j] != '\0')
            {
                //check if the thing right after the word is an allowed character
                if(text[find_i + i] == custom_end[j]) 
                {
                    return false;
                }
                j++;
            }
            return true;
        }else {
            int j = 0;
            while(custom_end[j] != '\0') {
                //check if the thing right after the word is an allowed character
                if(text[find_i + i] == custom_end[j])  {
                    return true;
                }
                j++;
            }
            return false;
        }
    }
}

bool checkstr(const char* text, const char* find, int find_i, bool ignore_case, const char* custom_end, bool exclude_end, const char* custom_start, bool exclude_start) {
    int text_len = strlen_tk(text);
    int find_len = strlen_tk(find);
    return checkstr(text, text_len, find, find_len, find_i, ignore_case, custom_end, exclude_end, custom_start, exclude_start);
}

bool checkstr(const char* text, int text_len, const char* origin, Parser::Arg find, int find_i, bool ignore_case, const char* custom_end, bool exclude_end, const char* custom_start, bool exclude_start) {
    return checkstr(text, text_len, origin + find.i, find.len, find_i, ignore_case, custom_end, exclude_end, custom_start, exclude_start);
}

bool checkstr(const char* text, const char* origin, Parser::Arg find, int find_i, bool ignore_case, const char* custom_end, bool exclude_end, const char* custom_start, bool exclude_start) {
    int text_len = strlen_tk(text);
    return checkstr(text, text_len, origin + find.i, find.len, find_i, ignore_case, custom_end, exclude_end, custom_start, exclude_start);
}

/**
 * @brief function that gets the current line based on provided index and global input string variable (counts the number of \n characters before the index)
 * @param i the provided index where the code is going to base its search on
 */
int get_line(const char*  input, int i)
{
    //count the number of new line characters before the index
    int n_of_new_line_char = 0;
    int j = i;
    while(j >= 0)
    {
        //if found a new line character increase the counter
        if(input[j] == '\n')
        {
            n_of_new_line_char++;
        }

        j--;
    }

    //return 1 + the number of new line characters since line 1 starts at number of char 0
    return 1 + n_of_new_line_char;
}
int get_line(std::string& input, int i) {return get_line(input.c_str(), i);}

/**
 * @brief function that gets the current character of the current line based on provided index and global input string variable (counts the number of characters between current index and last new line)
 * @param i the provided index where the code is going to base its search on
 */
int get_char(const char* input, int i)
{
    //find the last new line character
    int last_new_line_char = i;
    while(input[last_new_line_char] != '\n' && last_new_line_char >= 0)
    {
        last_new_line_char--;
    }

    //return the difference between current index "i" and the index of the last new line character (finds the number of characters between them)
    return i - last_new_line_char;
}
int get_char(std::string& input, int i) {return get_char(input.c_str(), i);}

std::string get_pos(const char* input, int i) {
    std::string output = std::to_string(get_line(input, i)) + ":" + std::to_string(get_char(input, i));
    return output;
}
std::string get_pos(std::string& input, int i) {return get_pos(input.c_str(), i);}

/**
 * @param i the index of the line you want to print
 * @brief from index `i` prints from last new line character to the next new line character (prints the current line)
 * @return returns an integer representing the index of the last new line character
 */
int print_curr_line(const char* input, int input_len, int i) {
    
    //print the last line {
    #if true
    
        //find the last new line character
        int last_new_line_char = i - 1;
        while(input[last_new_line_char] != '\n' && last_new_line_char >= 0)
        {
            last_new_line_char--;
        }

        //find the next new line character
        int next_new_line_char = i;
        while(input[next_new_line_char] != '\n' && next_new_line_char < input_len)
        {
            next_new_line_char++;
        }

        //print everything that is in between those two characters
        for(int j = last_new_line_char + 1; j <= next_new_line_char - 1; j++)
        {
            if(j >= input_len)
            {
                print("\\0");
            }else
            {
                print(input[j]);
            }
        }

        //print a new line to end this printed line
        println();

    #endif
    //}
    
    return last_new_line_char;//return the index of the last new line character
}

/**
 * @brief function to visually show where indexes are in a string
 * @param i the startin index of the range
 * @param iend the ending index of the range (defaults to the same value as i when not specified (i.e. a range of indexes of length 1))
 * @param input the string you want to look at
 * @param handle_multi_byte this stops the cursor on multi byte characters to let the index catch up (Parser class skips the continuation bytes of multi byte characters, this function also does this skipping by default, this results in a double skip, to remediate this issue make this value true)
 * @param align_next_line adds the same 
 * 
 * #### Examples:
 * 
 * ##### single index (at 8) :
 * ```txt
 * this is the string
 *         ^
 * ```
 * 
 * ##### range of indexes (from 8 to 17) :
 * ```txt
 * this is the string
 *   ­ ­ ­ ­ ­ ­ ­[########]
 * ```
 * 
 * ##### 0 length range of indexes (from 8 to 7)
 * ```txt
 * this is the string
 *         ⎸
 * ```
 * 
*/
void display_info(const char* input, int input_len, int i, int iend, bool handle_multi_byte, bool align_next_line)
{
    if(iend == INT_MIN)
    {
        iend = i;
    }
    
    //print the current line and set last_new_line_char index to what the function outputs
    int last_new_line_char = print_curr_line(input, input_len, i);

    //display a little arrow to point where we saw the supposed keyword {
    #if true
        //print all required spaces before the little arrow
        for(int j = last_new_line_char + 1; j < i; j++)
        {
            if(handle_multi_byte) {
                if(0x80 <= (uint8_t)(input[j]) && (uint8_t)(input[j]) <= 0xBF) continue;//skip the continuation byte of multi byte characters
            }
            print(" ");
        }

        if(iend - i + 1 == 0) {
            //print a bar to indicate zero length
            println("⎸");
        }else if(i == iend)
        {
            //print the little arrow and new line
            println("^");
        }else
        {
            //create variable to remember the current index we are printing
            int curr_i = i - 1;

            //print a range 
            print("["); curr_i++;

            //get length of range
            int len = iend - i + 1;
            
            //print all required spaces before the little arrow
            for(int j = 0; j < len - 2; j++)
            {
                if(handle_multi_byte) {
                    if(0x80 <= (uint8_t)(input[j]) && (uint8_t)(input[j]) <= 0xBF) continue;//skip the continuation byte of multi byte characters
                }

                print("#"); curr_i++;                

                //when we reach a new line, we should be printing the next line in the "input"
                if(input[curr_i] == '\n') {
                    //print extra new line (extend the info displaying to a new line)
                    println();

                    //set the current index to the index we currently printed the # on
                    int i = curr_i + 1;

                    //print the current line
                    last_new_line_char = print_curr_line(input, input_len, i);
                }
            }

            //print a range 
            println("]"); curr_i++;
        }
    #endif 
    //}

    //add some spaces for the next line to be aligned with the current thing {
    #if true
        //if align next line, we shall print extra start spaces to match the "^"
        if(align_next_line) {
            //print all required spaces before the little arrow
            for(int j = last_new_line_char + 1; j < i; j++)
            {
                if(handle_multi_byte) {
                    if(0x80 <= (uint8_t)(input[j]) && (uint8_t)(input[j]) <= 0xBF) continue;//skip the continuation byte of multi byte characters
                }
                print(" ");
            }
        }
    #endif
    //}

}

void display_info(const char* input, int i, int iend, bool handle_multi_byte, bool align_next_line) {
    return display_info(input, strlen_tk(input), i, iend, handle_multi_byte, align_next_line);
}

void display_info(std::string input, int i, int iend, bool handle_multi_byte, bool align_next_line) {
    display_info(input.c_str(), i, iend, handle_multi_byte, align_next_line);
}

void display_info(const char* input, Parser::Arg arg, bool handle_multi_byte, bool align_next_line) {
    display_info(input, arg.i, arg.i + arg.len - 1, handle_multi_byte, align_next_line);
}

void display_info(std::string& input, Parser::Arg arg, bool handle_multi_byte, bool align_next_line) {
    display_info(input.c_str(), arg.i, arg.i + arg.len - 1, handle_multi_byte, align_next_line);
}

/**
 * @brief takes a c-string (character array) and pushes/moves all elements from index to the end by the desired amount
 * @param str the c-string (character array) you want to modify
 * @param size the size of the c-string (character array) you want to modify (a size of -1 can be attributed to skip size checking all together)
 * @param i the index at which you start to push (index `i` is included in the push)
 * @param push_by the amount that all values from `i` to end get pushed by
 * @note your character array must be able to fit the pushed back characters, (your string has to be at be able to accomodate `push_by` amount of extra characters)
 */
void push_h(char* str, int size, int i, int push_by, LINE_TRACKER)
{
    size--;//technically the real size of a string because you need to fit the nullcharacter at the end
    int end   = strlen_tk(str) - 1; //index of the nullcharacter (included in the move)
    int start = 0;           //index of the start character (always 0 for C++)
    
    if(push_by < 0)
    {
        i -= push_by; //adjust to make push delete stuff at the index and going to the right instead of going to the left
        
        //print a detailed error if we know the push by is going to fail
        if(size != -1 && (end + push_by) >= size)
        {
            //print an error message with details about the line where it happent
            println(ERROR_LINE,"tried to move ",end," to ",end + push_by," (which is out of the range of the array), range of possible indexes are [",start,"-",size - 1,"] (this error happens for indexes ",size - push_by,"-",end," or ",end - size + push_by + 1," times)");
        }

        // going from (end) to (i) moving everything to the left by `push_by`amount
        for (int j = (i); j <= (end); j++)
        {
            //if move is in a valid range
            if(size == -1 || (j + push_by) < size)
            {
                //displace the data
                str[j + push_by] = str[j];
            }
        }

        //add the nullcharacter at the end of the string
        str[end + 1 + push_by] = '\0';
    }else
    {
        //print a detailed error if we know the push by is going to fail
        if(size != -1 && (end + push_by) >= size)
        {
            //print an error message with details about the line where it happent
            println(ERROR_LINE,"tried to move ",end," to ",end + push_by," (which is out of the range of the array), range of possible indexes are [",start,"-",size - 1,"] (this error happens for indexes ",size - push_by,"-",end," or ",end - size + push_by + 1," times)");
        }

        /* going from (end) to (i) moving everything to the left by `push_by`amount

        Example of what this code is doing :

        "I am a string and I want to be pushed back"
        ^                                        ^
        start                                    end

        lets say that push_by was 5;

        push_by = 5;

        "I am a string and I want to be pushed back"
                                                ^   ^
                                        move this   over there
        
        "I am a string and I want to be pushed bac "  k
                                                ^   ^
                                        move this   over there

        "I am a string and I want to be pushed ba  " ck
                                                ^   ^
                                        move this   over there

                        and etc.. until you reach the index you want to stop at
        
                        
        */
        for (int j = (end); j >= (i); j--)
        {
            //if move is in a valid range
            if(size == -1 || (j + push_by) < size)
            {
                //displace the data
                str[j + push_by] = str[j];
            }
        }

        //add the nullcharacter at the end of the string
        str[end + 1 + push_by] = '\0';
    }
}

#define pushstr(str, i, push_by) (push_h(str, sizeofarray(str), i, push_by))

std::string readfile(const char* filePath, LINE_TRACKER)
{
    std::ifstream f(filePath);

    if(!f.is_open()) {
        // file doesn't exist or can't be opened
        println(ERROR_LINE,"could open file \"",filePath,"\" (make sure the file exists)");
        return "";
    }

    // whole file into one string
    std::string output((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());

    f.close();

    return output;
}
void setfile(const char* filePath, std::string str, LINE_TRACKER)
{
    //open file
    std::ofstream f(filePath);

    //check for failed open
    if(!f.is_open()) {
        // file doesn't exist or can't be opened
        println(ERROR_LINE,"could open file \"",filePath,"\" (make sure the file exists)");
        return;
    }
    
    //override file with string
    f << str;
    f.close();
}
void appendfile(const char* filePath, std::string str, LINE_TRACKER) {
    //open file
    std::ofstream f(filePath, std::ios::app);

    //check for failed opening
    if(!f.is_open()) {
        //file doesn't exist or can't be opened
        println(ERROR_LINE,"could open file \"",filePath,"\" (make sure the file exists)");
        return;
    }

    //append to the file (std::ios::app (i.e. append mode) set when opening the file)
    f << str;
    f.close();
}

long long recorded_time[10];
long long recorded_index = 0;
void ts(LINE_TRACKER)
{
    if(0 <= recorded_index && recorded_index < sizeofarray(recorded_time)) {
        recorded_time[recorded_index] = millis();
        recorded_index++;
    }else if(0 <= recorded_index && sizeofarray(recorded_time) <= recorded_index) {
        println(ERROR_LINE,"maximum of time saves (",sizeofarray(recorded_time),") got reached (",recorded_index,"), cannot add a time save");
        recorded_index++;
    }else if (recorded_index < 0 && recorded_index < sizeofarray(recorded_time)) {
        println(ERROR_LINE,"minimum of time saves (",0,") got reached (",recorded_index,"), cannot add a time save");
        recorded_index++;
    }
}

long long te(LINE_TRACKER)
{
    recorded_index--;
    if(0 <= recorded_index && recorded_index < sizeofarray(recorded_time)) {
        return millis() - recorded_time[recorded_index];
    }else if(0 <= recorded_index && sizeofarray(recorded_time) <= recorded_index) {
        println(ERROR_LINE,"ts() got called too many times");
        return -1;
    }else if (recorded_index < 0 && recorded_index < sizeofarray(recorded_time)) {
        println(ERROR_LINE,"te() got called too many times");
        return -1;
    }else {
        println(ERROR_LINE,"unknown error, sorry to dissapoint :(");
        return -1;
    }
}

uint64_t recorded_time_us[10];
uint64_t recorded_index_us = 0;
void tus(LINE_TRACKER)
{
    if(0 <= recorded_index_us && recorded_index_us < sizeofarray(recorded_time_us)) {
        recorded_time_us[recorded_index_us] = micros();
        recorded_index_us++;
    }else if(0 <= recorded_index_us && sizeofarray(recorded_time_us) <= recorded_index_us) {
        println(ERROR_LINE,"maximum of time saves (",sizeofarray(recorded_time_us),") got reached (",recorded_index_us,"), cannot add a time save");
        recorded_index_us++;
    }else if (recorded_index_us < 0 && recorded_index_us < sizeofarray(recorded_time_us)) {
        println(ERROR_LINE,"minimum of time saves (",0,") got reached (",recorded_index_us,"), cannot add a time save");
        recorded_index_us++;
    }
}

uint64_t tue(LINE_TRACKER)
{
    recorded_index_us--;
    if(0 <= recorded_index_us && recorded_index_us < sizeofarray(recorded_time_us)) {
        return micros() - recorded_time_us[recorded_index_us];
    }else if(0 <= recorded_index_us && sizeofarray(recorded_time_us) <= recorded_index_us) {
        println(ERROR_LINE,"ts() got called too many times");
        return -1;
    }else if (recorded_index_us < 0 && recorded_index_us < sizeofarray(recorded_time_us)) {
        println(ERROR_LINE,"te() got called too many times");
        return -1;
    }else {
        println(ERROR_LINE,"unknown error, sorry to dissapoint :(");
        return -1;
    }
}

void testRandomProbabilities(int min_r, int max_r, long (*random)(long s, long e), long long n_of_iterations = 100000000) {
        
    const size_t n_of_times_size = max_r - min_r + 1;
    int n_of_times[n_of_times_size];
    clearArray(n_of_times, 0);


    //default min and max value (least good min and max)
    int min_r_found = INT_MAX;
    int max_r_found = INT_MIN;

    //loop to find all random possibilities
    for(long long i = 0; i < n_of_iterations; i++) {
        //get supposed random number in between range
        long r = random(min_r, max_r);

        //update n_of_times array
        int index = r - min_r;
        n_of_times[index]++;

        //check if better options, if yes replace¸
        if(r < min_r_found) min_r_found = r;
        if(r > max_r_found) max_r_found = r;

        //nice percentage bar thingy
        percentageBar(0, i, n_of_iterations - 1, 100, 2);
    }

    DEBUG_BANNER("mininum and maximum random values found");
    DEBUG(min_r_found, max_r_found);


    int probability_precision = 100000000;

    println();
    DEBUG_BANNER("probability list");
    for(int i = 0; i < n_of_times_size; i++) {
        //get corresponding number
        int n = i + min_r;
        
        //Get corresponding number of times
        int t = n_of_times[i];

        

        //figure out number of space between to equalize everything
        int n_of_space = 5 - getLen(n);

        //print spaces
        for(int k = 0; k < n_of_space; k++) {
            print(" ");
        }


        //Print the number
        print(n);

        //print little arrow with space before and after
        print("   ->   ");
        
        //get probability (n_of_iterations / total_n_of_iterations)
        int prob = (long long)(t) * (long long)(probability_precision) / (long long)(n_of_iterations);

        //print the probability
        print(prob," / ",probability_precision);

        println();
    }
    }
    
int findstr(const char* text, int text_len, const char* find, int find_len, int search_start, bool ignore_case, const char* custom_end, bool exclude_end, const char* custom_start, bool exclude_start, LINE_TRACKER_SHELL) {    
    if(search_start >= strlen_tk(text)) {
        println("ERROR line ",line," in ",file," search_start is invalid (search start is ",search_start," while possible indexs are ",0,"-",strlen_tk(text) - 1,")");
    }

    if(text_len == -1) text_len = strlen_tk(text);
    if(find_len == -1) find_len = strlen_tk(find);
    
    //go through all of the string
    for(int i = search_start; i < text_len; i++) {
        //check for a string matching the function inputs
        bool found = checkstr(text, text_len, find, find_len, i, ignore_case, custom_end, exclude_end, custom_start, exclude_start);

        //if we found a match
        if(found) {
            //return the index
            return i;
        }
    }

    //if we didn't find the index, return -1
    return -1;
}

int findstr(const char* text, const char* find, int search_start, bool ignore_case, const char* custom_end, bool exclude_end, const char* custom_start, bool exclude_start, LINE_TRACKER_SHELL) {
    int text_len = strlen_tk(text);
    int find_len = strlen_tk(find);
    return findstr(text, text_len, find, find_len, search_start, ignore_case, custom_end, exclude_end, custom_start, exclude_start, LINE_TRACKER_INPUT);
}

int findstr(const char* text, int text_len, const char* origin, Parser::Arg find, int search_start, bool ignore_case, const char* custom_end, bool exclude_end, const char* custom_start, bool exclude_start, LINE_TRACKER_SHELL) {
    return findstr(text, text_len, origin + find.i, find.len, search_start, ignore_case, custom_end, exclude_end, custom_start, exclude_start, LINE_TRACKER_INPUT);
}

int findstr(const char* text, const char* origin, Parser::Arg find, int search_start, bool ignore_case, const char* custom_end, bool exclude_end, const char* custom_start, bool exclude_start, LINE_TRACKER_SHELL) {
    int text_len = strlen_tk(text);
    return findstr(text, text_len, origin + find.i, find.len, search_start, ignore_case, custom_end, exclude_end, custom_start, exclude_start, LINE_TRACKER_INPUT);
}


//chunk storer class (act as a vector of pointers to chunks)
template<typename T>
class vector {
    public:
    T*      elements;//chunk array stores elements
    int     len     ;//the length of the chunks

    //add a new element to the end of the array
    void add(T element, int index, LINE_TRACKER) {
        int new_len = len + 1;//adding an element to the end so new length will be one more
        
        //error check
        if(index < 0 || new_len <= index) {
            println(ERROR_LINE,"the index specified to add a new element at was invalid (out of bounds), you inputed ",index," while possible indexes range from ",0," to ",new_len - 1);
            return;//early return due to error
        }

        T* new_chunks = new T[new_len];//reserve chunk in memory for new chunks array

        //copy over previous array up to the specified index
        for(int i = 0; i < index; i++) {
            new_chunks[i] = elements[i];
        }

        //add chunk at index
        new_chunks[index] = element;

        //copy over rest of the array
        for(int i = index + 1; i < index; i++) {
            new_chunks[i] = elements[i - 1];
        }

        //we no longer need the old chunks and length replace by new
        if(elements != nullptr) delete[] elements;//no memory leaks
        elements = new_chunks;
        len    =   new_len   ;
    }

    //defaults to adding to the end if index was not specified equivalent to using operator+=
    void add(T element, LINE_TRACKER) {
        add(element, len, FND(), line, file);//forward arguments to original add function
    }

    void operator+=(LineTracker<T> element) {
        add(element.value, FND(), element.line, element.file);
    }

    void add(T* data, int data_len, int index, LINE_TRACKER) {
        int new_len = len + data_len;//adding an element to the end so new length will be one more
        
        //error check
        if(index < 0 || new_len <= index) {
            println(ERROR_LINE,"the index specified to add a new element at was invalid (out of bounds), you inputed ",index," while possible indexes range from ",0," to ",new_len - 1);
            return;//early return due to error
        }

        T* new_chunks = new T[new_len];//reserve chunk in memory for new chunks array

        //copy over previous array up to the specified index
        for(int i = 0; i < index; i++) {
            new_chunks[i] = elements[i];
        }

        //copy over the data
        for(int i = 0; i < data_len; i++) {
            new_chunks[i + index] = data[i];
        }

        //copy over rest of the array
        for(int i = index + data_len; i < index; i++) {
            new_chunks[i] = elements[i - data_len];
        }

        //we no longer need the old chunks and length replace by new
        if(elements != nullptr) delete[] elements;//no memory leaks
        elements = new_chunks;
        len    = new_len   ;
    }

    void add(T* data, int data_len, int index, int repeat_n, LINE_TRACKER) {
        int new_len = len + data_len * repeat_n;//adding an element to the end so new length will be one more
        
        //error check
        if(index < 0 || new_len <= index) {
            println(ERROR_LINE,"the index specified to add a new element at was invalid (out of bounds), you inputed ",index," while possible indexes range from ",0," to ",new_len - 1);
            return;//early return due to error
        }

        T* new_chunks = new T[new_len];//reserve chunk in memory for new chunks array

        //copy over previous array up to the specified index
        for(int i = 0; i < index; i++) {
            new_chunks[i] = elements[i];
        }

        //repeat specified number of times
        for(int j = 0; j < repeat_n; j++) {
            //copy over the data
            for(int i = 0; i < data_len; i++) {
                new_chunks[i + index] = data[i];
            }
        }

        //copy over rest of the array
        for(int i = index + data_len * repeat_n; i < index; i++) {
            new_chunks[i] = elements[i - data_len];
        }

        //we no longer need the old chunks and length replace by new
        if(elements != nullptr) delete[] elements;//no memory leaks
        elements = new_chunks;
        len    = new_len   ;
    }

    //get a chunk at a specific index
    T& at(int index, LINE_TRACKER) {
        //error check
        if(index < 0 || len - 1 < index) {
            println(ERROR_LINE,"the index specified in the \"at\" function was invalid (out of bounds), you inputed ",index," while possible indexes range from ",0," to ",len - 1);
            
            static T t;
            return t;//early return due to error
        }

        return elements[index];
    }

    T operator[](int index) {
        return elements[index];
    }

    //clear the whole array
    void clear() {
        //no memory leaks
        if(elements != nullptr) delete[] elements;
        elements = nullptr;
        len      = 0      ;
    }

    void resize(int index, int length, LINE_TRACKER) {
        int new_len = length;//adding an element to the end so new length will be one more
        
        //error check
        if(index < 0 || len - new_len <= index) {
            println(ERROR_LINE,"the index specified to resize was invalid (out of bounds), you inputed ",index," while possible indexes range from ",0," to ",len - new_len);
            return;//early return due to error
        }

        T* new_chunks = new T[new_len];//reserve chunk in memory for new chunks array

        //take resize snippet and put it in the new array
        for(int i = 0; i < length; i++) {
            new_chunks[i] = elements[i + index];
        }

        //we no longer need the old chunks and length replace by new
        if(elements != nullptr) delete[] elements;//no memory leaks
        elements = new_chunks;
        len      = new_len   ;
    }

    //resize with only length
    void resize(int length, LINE_TRACKER) {
        resize(0, length, FND(), line, file);
    }

    void debug() {
        printarray_h(elements, len);
    }

    int size()   {return len;}
    int length() {return len;}
    

    //no copying vectors bitch, I didn't implement that yet
    vector(const vector& other) = delete;
    operator=(const vector& other) = delete;


    vector() {
        //set default start values
        elements = nullptr;
        len    = 0      ;
    }

    ~vector() {
        clear();
    }
};

std::string base64_encode(const uint8_t* data, int length) {

    const char* transl = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    //what are the number of bits of each little base64 groups we want to extract and transform into
    const int new_group_bits_c = 6;

    //figure out group counts
    const int orig_group_c = 3;                                    //go through each group of 3 characters
    const int new_group_c  = (orig_group_c * 8) / new_group_bits_c;//get correct new group count based on the group bit size

    //create a buffer to store the base64 encoding output
    char* buff = new char[CEIL((double)(length) / orig_group_c) * new_group_c + 1];//use ceiling to store the padding (+1 for \0 at the end)
    int  len = 0;                                                                        //current length of the buffer

    for(int i = 0; i < length; i += orig_group_c) {
        uint32_t combined = 0;
        
        //put a snippet of 3 bytes in combined
        for(int j = 0; j < orig_group_c; j++) {
            if(i + j  >= length) break;                    //skip padding characters
            uint32_t c = data[i + j];                      //get current character
            combined  |= c << ((orig_group_c - j - 1) * 8);//add to the combined character
        }

        //translate snippet of 3 bytes
        const int mask  = (1 << new_group_bits_c) - 1;//0b1111... of length "new_group_bits_c"
        for(int j = 0; j < new_group_c; j++) {
            //the current character of the base64 encoded output string
            char c = 0;

            //if not padding
            if(j * orig_group_c / new_group_c + i < length) {
                int shift = (new_group_c - j - 1) * new_group_bits_c;//calculate how much we are going to shift the mask
                int chunk = (combined & (mask << shift)) >> shift   ;//get the correct snippet of combined
                c         = transl[chunk]                           ;//translate the number in that chunk to its corresponding base64 character
            }else {
                c = '=';//apply padding character to fill rest of the string
            }

            //add the translated character to the end of the output buffer
            buff[len] = c;
            len++;
        }
    }

    //add terminating \0 character
    buff[len] = '\0';

    std::string output = std::string(buff, len);
    delete[] buff;
    
    //return the buffer
    return output;
}
std::string base64_encode(const char* data) {
    int length = strlen_tk(data);
    return base64_encode((const uint8_t*)(data), length);
}
std::string base64_encode(std::string data) {
    return base64_encode((const uint8_t*)(data.c_str()), data.length());
}

template<typename T>
void convert_hex(T n, char* buff, int buff_len, LINE_TRACKER) {
    for(int i = 0; i < sizeof(T) * 8 / 4; i++) {
        if(i < 0 || buff_len - 1 < i) {
            println(ERROR_LINE,"the index of the loop went out of bounds (the buffer provided was most likely too short)");
        }else {
            buff[buff_len - 1 - i] = hex_numbers[(n & (0b1111ULL << (unsigned long long)(i * 4))) >> (i * 4)];
        }
    }
}

//universale byte swap for any numbers
template<typename T>
T b_swap(T num) {
    const int32_t n_of_bytes = sizeof(num);//calculate number of bytes of number `num`
    
    //store result
    T result = 0;

    //for each byte in the number
    for(int i = 0; i < n_of_bytes; i++) {
        uint8_t byte = (num >> (8 * i)) & 0b11111111;//get the current byte in the number `num`
        int     inverted_i = n_of_bytes - 1 - i;     //get the inverted byte index for following equation

        result |= byte << (8 * (inverted_i));        //slot byte at the inverted index (starting bytes go to end and ending bytes go to start) (i.e. invert byte order)
    }

    return result;
}


//universale number to array (big endian by default)
//the output in the array is big endian by default
//big    endian -> like normal numbers     e.g.     big first -> 1234 <- then small
//little endian -> the opposite, small first, then big
template<int len, typename T>
void num_to_arr(T num, uint_least8_t array[len], bool little_endian = false, LINE_TRACKER) { 
    uint8_t*      arr        = (uint8_t*)(array);//alias to array with indexing width of 8 bits
    const int32_t n_of_bytes = sizeof(num);      //calculate number of bytes of number `num`
    
    //for each byte in the number
    for(int i = 0; i < n_of_bytes; i++) {
        uint8_t byte = (num >> (8 * i)) & 0b11111111;//get the current byte in the number `num`
        
        //set bytes in the array depending ont the endian chosen
        int true_i;
        if(little_endian) {
            true_i = i;
        }else {
            int inverted_i = n_of_bytes - 1 - i;
            true_i = inverted_i;
        }

        DEBUG_BOUND(len, true_i);

        arr[true_i] = byte;
    }
}




const static int block_size = 64;
std::string sha1_encode(const uint8_t* data, int32_t data_len) {
    const char* datastr = (const char*)(data);

    
    /* steps to sha1 :
        1. add a single 1 bit to the end of your message.

        2. add a bunch of 0 bits until the length is exactly 64 bits short of a multiple of 512.

        3. In that remaining 64 bits, write the original length of your message (as a binary number).
    
        4. each 512 chunk of the message are split into 16 chunks of 32 bits each

        5. extend 16 chunks (called words) into 80 words... here's an example on how to compute a new word
            for i in range(16, 80):
                # This is the famous SHA-1 mixing formula
                new_word = words[i-3] ^ words[i-8] ^ words[i-14] ^ words[i-16]
                # Rotate the bits left by 1 (the '<< 1' and the '& 0xFFFFFFFF' keeps it within 32 bits)
                new_word = ((new_word << 1) | (new_word >> 31)) & 0xFFFFFFFF
                words.append(new_word)

        6. mix the states around using the calculated words... 
            here are the states (each state is 32 bits) : 
                a, b, c, d, e = h0, h1, h2, h3, h4
            and here is an example code emulating this jumbling around : 
                for i in range(80):
                    # Pick which logical function to use (SHA-1 uses 4 different ones)
                    if 0 <= i < 20:
                        f = (b & c) | ((~b) & d)
                        k = 0x5A827999  # Constant number for this round
                    elif 20 <= i < 40:
                        f = b ^ c ^ d
                        k = 0x6ED9EBA1
                    elif 40 <= i < 60:
                        f = (b & c) | (b & d) | (c & d)
                        k = 0x8F1BBCDC
                    else:
                        f = b ^ c ^ d
                        k = 0xCA62C1D6
                    
                    # The core calculation:
                    temp = ((a << 5) | (a >> 27)) & 0xFFFFFFFF  # Rotate A left by 5
                    temp = (temp + f + e + k + words[i]) & 0xFFFFFFFF
                    
                    # Shift everything down the line
                    e = d
                    d = c
                    c = ((b << 30) | (b >> 2)) & 0xFFFFFFFF  # Rotate B left by 30
                    b = a
                    a = temp
        
        7. add back a, b, c, d, e to their respective h0, h1, h2, h3, h4 
        
        8. combine all the 32 bit scratch pad variables converted in hex together into one big hex number
    */
    
    //original scratchpad values official SHA1 always starts with these
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    //compute how many bits the data is
    int64_t data_bit_len = data_len * 8; 
    int64_t padding_len  = 1 + 64;//minimum 65 bit len of padding (1bit + 64bit length) (skips to next block if we don't have enough space for length)

    //add padding until we are at a multiple of 512 (64 * 8)
    while((data_bit_len + padding_len) % (block_size * 8) != 0) padding_len++;

    int64_t total_len = data_bit_len + padding_len;

    //compute the number of 512 chunks we will need to allocate
    int32_t chunk_n = total_len / (block_size * 8);

    //allocate an array to store the chunk pointers
    uint8_t** chunks = new uint8_t*[chunk_n];

    //for each chunks pointer, associate a 512 chunk to it containing the correct data
    for(int i = 0; i < chunk_n; i++) {
        //allocate 512 bit chunk and set current index to it
        uint8_t* chunk = new uint8_t[block_size];
        chunks[i] = chunk;

        //clear chunk
        for(int j = 0; j < block_size; j++) chunk[j] = 0;
    }

    //add data to the chunks
    for(int i = 0; i < data_len; i++) {
        //calculate which chunk and which index in that chunk
        int chunk_i      = i / block_size;
        int chunk_data_i = i % block_size;

        DEBUG_BOUND(chunk_n, chunk_i);

        //add one byte of data to the chunks
        chunks[chunk_i][chunk_data_i] = data[i];
    }

    //add the 1 bit right after the data
    {
        int chunk_i      = data_len / block_size;
        int chunk_data_i = data_len % block_size;

        DEBUG_BOUND(chunk_n, chunk_i);

        chunks[chunk_i][chunk_data_i] = 0b10000000;
    }

    //add the length of the message as a 64 bit number at the end of the last 512 chunk
    if(chunk_n >= 1) {
        int chunk_i      = chunk_n - 1;
        int chunk_data_i = block_size - sizeof(uint64_t);

        // Store the length as a 64-bit big-endian number
        uint64_t bit_len = (uint64_t)data_len * 8;

        // Write each byte in big-endian order
        for (int j = 0; j < 8; j++) {
            chunks[chunk_i][chunk_data_i + j] = (bit_len >> (56 - j * 8)) & 0xFF;
        }
    }

    //then do some weird encription steps repeated on each 512 chunks
    for(int i = 0; i < chunk_n; i++) {

        //get current chunk
        uint8_t* chunk = chunks[i];

        //make word array this array's length will end up being 80 words long
        uint32_t words[80] = {};

        //the first 16 words of this array comes from the chunk cut into parts of 32 bits
        for(int j = 0; j < block_size / sizeof(uint32_t); j++) {
            // Read bytes directly from chunk (no pointer casting)
            uint32_t word = 0;
            word |= (uint32_t)chunk[j * sizeof(uint32_t) + 0] << 24;
            word |= (uint32_t)chunk[j * sizeof(uint32_t) + 1] << 16;
            word |= (uint32_t)chunk[j * sizeof(uint32_t) + 2] << 8 ;
            word |= (uint32_t)chunk[j * sizeof(uint32_t) + 3];
            words[j] = word;
        }

        //generate the extra 64 words by using a complex xor bitwise shift algorithm
        for(int j = 16; j < 80; j++) {
            //SHA1 mixing forumla
            uint32_t new_word = words[j - 3] ^ words[j - 8] ^ words[j - 14] ^ words[j - 16];

            //rotate bits left by 1
            new_word = (new_word << 1) | (new_word >> 31);
        
            //add the new word at the end of the words array
            words[j] = new_word;
        }

        //make a copy of the original scratch pads h0-h4
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        for(int j = 0; j < 80; j++) {

            //temporary variables that I don't konw why are there
            uint32_t f = 0;
            uint32_t k = 0;
            
            // pick logical SHA 1 function to use (total of 4)
            if      ( 0 <= j && j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }else if(20 <= j && j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }else if(40 <= j && j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }else if(60 <= j && j < 80) {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            //core calculation : 
            uint32_t temp;
            temp = (a << 5) | (a >> 27); //rotate a left by 5
            temp = temp + f + e + k + words[j];

            //shift everything down the line
            e = d;
            d = c;
            c = (b << 30) | (b >> 2); // rotate b left by 30
            b = a;
            a = temp;

        }
        
        //add a, b, c, d, e to their respective h0, h1, h2, h3, h4
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;

    }

    //no memory leaks
    if(chunks != nullptr) {
        for(int i = 0; i < chunk_n; i++) {
            if(chunks[i] != nullptr) delete[] chunks[i];
        }
        delete[] chunks;
        chunks = nullptr;
    }

    //now with the h0-h4 variables, we convert each to hex and concat them together
    const static int output_len = 20;
    uint8_t output[output_len] = {};//allocate 40 characters for output

    //put the number into the char array
    num_to_arr<output_len -  0>(h0, output +  0);
    num_to_arr<output_len -  4>(h1, output +  4);
    num_to_arr<output_len -  8>(h2, output +  8);
    num_to_arr<output_len - 12>(h3, output + 12);
    num_to_arr<output_len - 16>(h4, output + 16);

    //copy output over to a std::string variable to ship it for output
    std::string output_str((const char*)(output), output_len);

    //return the output string
    return output_str;
}
std::string sha1_encode(const char*    data) {
    int32_t data_len = strlen_tk(data);
    return sha1_encode((const uint8_t*)(data), data_len);
}
std::string sha1_encode(std::string data) {
    return sha1_encode((const uint8_t*)(data.c_str()), data.length());
}

const static uint8_t ipad_mask = 0x36;
const static uint8_t opad_mask = 0x5C;
std::string hmac_sha1_encode(const uint8_t* orig_key, int32_t key_len, const uint8_t* data, int32_t data_len) {
    uint8_t key[block_size] = {};

    //if the key is bigger than the sha1 block size (64 bytes)
    if(key_len > block_size) {
        //sha1 encode it to reduce it to the size of a block
        std::string new_key = sha1_encode(orig_key, key_len);
        
        //copy the new key in key
        for(int i = 0; i < new_key.length(); i++) {
            key[i] = new_key.c_str()[i];
        }
    }else {
        //if key hasn't been set yet, set it to orig_key (must be smaller than the block_size)
        for(int i = 0; i < key_len; i++) {
            key[i] = orig_key[i];
        }
    }

    //the key should now be the size of a sha1 block
    key_len = block_size;

    //create array to store both (inner pad + data) and (outer pad + inner hash)
    int pad_len = key_len + data_len;
    uint8_t* pad = new uint8_t[pad_len];//"block_size * 2" for starting and ending padding

    //inner padding + data    
    for(int i = 0; i < key_len ; i++) pad[i]           = ipad_mask ^ key[i];//inner padding
    for(int i = 0; i < data_len; i++) pad[key_len + i] = data[i]           ;//data

    //inner hash
    std::string inner_hash_str = sha1_encode(pad, pad_len);
    const uint8_t* inner_hash     = (const uint8_t*)(inner_hash_str.c_str());
    int            inner_hash_len = inner_hash_str.length();

    //outer padding + inner hash
    for(int i = 0; i < key_len       ; i++) pad[i]           = opad_mask ^ key[i];//outer padding
    for(int i = 0; i < inner_hash_len; i++) pad[key_len + i] = inner_hash[i]     ;//inner hash
    pad_len = key_len + inner_hash_len;//update length, for the (inner hash + outer padding)

    //do the finaly sha1 encode on the concatenated inner hash and outer padding
    std::string result = sha1_encode(pad, pad_len);

    //no memory leaks 
    delete[] pad;

    //return the hmac sha1 encode result 
    return result;
}
std::string hmac_sha1_encode(const char* orig_key, const char* data) {
    return hmac_sha1_encode((const uint8_t*)(orig_key), strlen_tk(orig_key), (const uint8_t*)(data), strlen_tk(data));
}
std::string hmac_sha1_encode(std::string orig_key, std::string data) {
    return hmac_sha1_encode((const uint8_t*)(orig_key.c_str()), orig_key.length(), (const uint8_t*)(data.c_str()), data.length());
}

//==================================================//
//                CUSTOM STRING CLASS               //
//==================================================//




class string {

    public: 
    char* str  = 0;
    long  len  = 0;

    //copy another string to the string class's buffer (used in constructor and operator=)
    void copy(const char* other, long other_len, LINE_TRACKER)
    {
        //temp debug: println("copying");

        if(other == nullptr && other_len != 0) {
            //make sure `other_len` is not 0 bcs if it is then nullptr pointer doesn't matter
            println(ERROR_LINE,"the str1 inputed inside of the insert command was nullptr");
            return;
        }

        //don't play this function if the "other" pointer is the same as our current `str` variable
        if(str == other) {return;}

        //dealocate previous string chunk if it exists
        if(str != nullptr) {
            delete[] str;
        }

        //set internal variables && request heap memory
        str = new char[other_len + 1];//+1 for null char at the end
        len = other_len;

        //copy string (other -> str)
        for(long i = 0; i < other_len; i++) {
            str[i] = other[i];
        }

        //add string end terminator
        str[other_len] = '\0';
    }

    //joins two strings together and copy them to the string class's internal buffer (used in operator+ and operator+=)
    void concat(const char* str1, long len1, const char* str2, long len2, LINE_TRACKER) {
        if(str1 == nullptr && len1 != 0) println(ERROR_LINE,"the str1 inputed inside of the insert command was nullptr");//make sure len1 is not 0 bcs if it is then nullptr pointer doesn't matter
        if(str2 == nullptr && len2 != 0) println(ERROR_LINE,"the str2 inputed inside of the insert command was nullptr");//make sure len2 is not 0 bcs if it is then nullptr pointer doesn't matter
        
        //figure out new chunk size (length of first string + length of second string)
        long new_len = len1 + len2;
        
        //get new chunk of memory large enough to accomodate our new string
        char* new_str = new char[new_len + 1];//+1 for null char

        //push the first string to the new string
        for(long i = 0; i < len1; i++) {
            new_str[i] = str1[i];//copy character by character
        }

        //push the second string to the new string (start right after first string (i.e. offset new_string index by len1)
        for(long i = 0; i < len2; i++) {
            new_str[len1 + i] = str2[i];
        }

        //add null char at the end of the string
        new_str[len1 + len2] = '\0';

        //dealocate previous str chunk
        if(str != nullptr) delete[] str;

        //set str to newly created string
        str = new_str;
        len = new_len;
    }

    //inserts a string at a specific index of the string (i.e. insert `str1` of length `len1` at index `index`)
    void insert(const char* str1, long len1, long index, LINE_TRACKER) {
        //error check, make sure inputed string isn't nullptr
        if(str1 == nullptr && len1 != 0) {
            //make sure len1 is not 0 bcs if it is then nullptr pointer doesn't matter
            println(ERROR_LINE,"the string inputed inside of the insert command was nullptr");
            return;
        }
        if(index < 0 || len <= index) {
            println(ERROR_LINE,"the index specified in the insert function (",index,") was out of bounds (possible indexes range from 0 to ",len - 1,")");
            return;
        }

        //calculate new length (must be current length + other string length)
        long new_len = len + len1;

        //request chunk of size `new_len` to fit the new string
        char* new_str = new char[new_len + 1];//+1 for null char

        //copy over current string up to just before index
        for(long i = 0; i < index; i++) {
            new_str[i] = str[i];
        }

        //push the string we wanted to insert (i.e. `str1`) to new_str (since first copy stopped just short of index, displacing by index so first iteration starts on index and goes on)
        for(long i = 0; i < len1; i++) {
            new_str[i + index] = str1[i];
        }

        //push last part of the string (start at index because we stopped just short of index on first copy) (adding displacement of len1 to skip newly pushed str1 in new_str)
        for(long i = index; i < len; i++) {
            new_str[i + len1] = str[i];
        }
        
        //add null terminator to new string
        new_str[len + len1] = '\0';

        //delete old previous string if it actually was set to something (we are about to replace it with new we don't need it anymore) 
        if(str != nullptr) delete[] str;

        //replace str and len internal variables by their new counterpart
        str = new_str;
        len = new_len;
    }
    void insert(const char* str1,            long index, LINE_TRACKER) {
        insert(str1, strlen_tk(str1), index, FND(), line, file);
    } 
    void insert(string      str1,            long index, LINE_TRACKER) {
        insert(str1.str, str1.len, index, FND(), line, file);
    }
    void insert(long index, const char* str1,            LINE_TRACKER) {
        insert(str1, strlen_tk(str1), index, FND(), line, file);
    }
    void insert(long index, string      str1,            LINE_TRACKER) {
        insert(str1.str, str1.len, index, FND(), line, file);
    }

    //erase a specific length from index 1 to index 2 INCLUSIVELY
    void erase(long istart, long iend, LINE_TRACKER) {
        //ERROR CHECKS
        if(istart < 0 || len <= istart) {
            println(ERROR_LINE,"the start index (or istart) specified (",istart,") was out of bounds (possible indexes range from 0 to ",len - 1,")");
            return;
        }
        if(iend < -1 || len <= iend) {
            println(ERROR_LINE,"the end index (or iend) specified (",iend,") was out of bounds (possible indexes range from -1 to ",len - 1,")");
            // println("tip: unlike std::string iend is inclusive not exclusive (i.e. the index you specify will be included in the range)");
            return;
        }
        

        //get the total length being reased in between i and iend
        long erased_len = iend - istart + 1;

        if(erased_len < 0) {
            println("WARNING/ERROR line ",line," in ",file,", the erased length (",erased_len,") is negative");
            return;
        }

        //calculate the length of the new string we will be creating
        long new_len = len - erased_len;

        //reserve part of memory for our new string
        char* new_str = new char[new_len + 1];//+1 for null char at the end

        //copy from start of string up to right before istart
        for(long i = 0; i < istart; i++) {
            new_str[i] = str[i];
        }

        //completely skip from istart to iend (to do so start at one after iend) (erased_len displacement to undo iend skip)
        for(long i = iend + 1; i < len; i++) {
            new_str[i - erased_len] = str[i];
        }

        //erase previous old string (we don't need it)
        if(str != nullptr) delete[] str;

        //replace str and len internal by new ones
        str = new_str;
        len = new_len;
    }

    void steal(string&& other) {
        println("weird operator I don't know about");
        str = other.str;
        len = other.len;
        
        other.str = nullptr;
        other.len = 0;
    }

    //easy one line functions (reroute existing values to specific functions)
    const char*  c_str() {
        if(str == nullptr) {
            return "";
        }else {
            return str;
        }
    }
    long         size()  {return len;           }
    long       length()  {return len;           }
    bool        empty()  {return str == nullptr;}

    //emulate clear function (simply dealocate the str and set length to 0) 
    void clear() {
        if(str != nullptr) delete[] str;
        str = nullptr;//set to default start
        len = 0      ;//set to default start 
    }

    // void   operator= (const char*                    other) {copy(other, strlen_tk(other));}
    void   operator= (const string&            other) {copy(other.str, other.len);}
    void   operator= (string&&                 other) {steal((decltype(other)&&)(other));}
    string operator+ (LineTracker<const char*  >     other) {
        string new_str;
        new_str.concat(str, len, other.value, strlen_tk(other.value), FND(), other.line, other.file);
        return new_str;//return the copy of the string
    }
    string operator+ (LineTracker<const string&>     other) {
        string new_str;
        new_str.concat(new_str.str, new_str.len, other.value.str, other.value.len, FND(), other.line, other.file);
        return new_str;//return the copy of the string
    }
    void   operator+=(LineTracker<const char*  >     other) {concat(str, len, other.value, strlen_tk(other.value), FND(), other.line, other.file);}
    void   operator+=(LineTracker<const string&>     other) {concat(str, len, other.value.str, other.value.len, FND(), other.line, other.file);}
    bool   operator==(const char*   other) {return strcmp_tk(str, other, len, strlen_tk(other)) == 0;}
    bool   operator==(const string& other) {return strcmp_tk(str, other.str, len, other.len) == 0;}
    bool   operator!=(const char*   other) {return !operator==(other);}
    bool   operator!=(const string& other) {return !operator==(other);}


    template<typename T>
    typename enable_if<is_number<T>::value, char&>::type
    operator[](T index) {return str[index];}
    
    operator const char*() {
        println("conversion to 'const char*' happent");
        //temp debug: println("played operator const char*");
        return c_str();
    }
    
    char& at(long index, LINE_TRACKER) {
        //error check
        if(index < 0 || len <= index) {
            println("ERROR, line ",line," in ",file,", in '",__func__,"' function of string class (e.g. at(index)), the index (",index,") was out of bounds (bounds are from 0 to ",len - 1,")"); 
            static char err_char = '\0';//return 0 (alias: '\0' or the null character)
            return err_char;
        }

        //return correct index
        return str[index];
    }

    string(){}//default constructor
    string(string&& other                         , LINE_TRACKER) {steal((decltype(other)&&)(other));}
    string(decltype(nullptr)                      , LINE_TRACKER) {println(ERROR_LINE,"you tried setting a string to nullptr");}
    string(const char* other, long other_len      , LINE_TRACKER) {copy(other, other_len, FND(), line, file);}                   //copy regular c-string (with length specified)
    string(const char* other                      , LINE_TRACKER) : string(other        , strlen_tk(other), FND(), line, file) {}//copy regular c-string
    string(const string& other                    , LINE_TRACKER) : string(other.str    , other.len       , FND(), line, file) {}//copy constructor
    string(const std::string& other               , LINE_TRACKER) : string(other.c_str(), other.length()  , FND(), line, file) {}//copy std::strings
    string(const char* origin, Parser::Arg snippet, LINE_TRACKER) : string(origin + snippet.i, snippet.len, FND(), line, file) {}//copy a snippet of a string

    template<size_t N> 
    string(char (&other)[N]) {
        println("copying a char array ref");
        if(other == nullptr) return;
        str = other;
        len = strlen_tk(other);
    }

    ~string() {
        println("destructor was called");

        //no memory leaks (i.e. memory used for nothing)
        if(str != nullptr) delete[] str;
    }

    
};

//if iostream library exists, then print overload to make raw string print correctly
#if IOSTREAM
    //overload for printing string
    std::ostream& operator<<(std::ostream& os, const string& str) {
        //print only if the string was actually set to something
        if(str.str != nullptr) {
            os << str.str;
        }

        return os;
    }
#endif

//==================================================//
//                CUSTOM STRING CLASS               //
//==================================================//



class ThreadLock {
    public:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    bool enable_debugging = 0;
    Tracker track;

    void lock(LINE_TRACKER) {
        if(enable_debugging) {
            println("atomic lock at line ",line," in ",file," (creation line ",track.line," in ",track.file,")");
        }

        while(flag.test_and_set()) {
            std::this_thread::yield();
        }
    }

    void unlock(LINE_TRACKER) {
        if(enable_debugging) {
            println("atomic unlock at line ",line," in ",file," (creation line ",track.line," in ",track.file,")");
        }

        flag.clear();
    }

    ThreadLock(LINE_TRACKER) {
        if(enable_debugging) {
            track.line = line;
            track.file = file;
        }
    }
};


class thread {
    std::thread t;
    thread(std::thread&& t) : t((std::thread&&)(t)) {}
    thread(std::thread& t) = delete;

    ~thread() {
        //wait before deleting the thread object
        if(t.joinable()) {
            t.join();
        }
    }
};











enum class DIR : uint8_t {
    UP    = 0b00,
    DOWN  = 0b01,
    LEFT  = 0b10,
    RIGHT = 0b11,
};

#if IOSTREAM
    std::ostream& operator<<(std::ostream& os, DIR dir) {
        switch(dir) {
            case DIR::UP   : os << "UP"   ; break;
            case DIR::DOWN : os << "DOWN" ; break;
            case DIR::LEFT : os << "LEFT" ; break;
            case DIR::RIGHT: os << "RIGHT"; break;
        }

        return os;
    }
#endif


struct Pointd;

struct Point;
DIR   to_dir(Point point, bool invert_y = 1);
Point to_point(DIR dir, bool invert_y = 1);

struct Point
{
    int16_t x;
    int16_t y;

    bool operator==(const Point& p)
    {
        return p.x == x && p.y == y;
    }

    bool operator!=(const Point& p)
    {
        return p.x != x || p.y != y;
    }

    Point operator+(const Point& p)
    {
        return {x + p.x, y + p.y};
    }

    Point& operator+=(const Point& p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point& operator+=(int n)
    {
        x += n;
        y += n;
        return *this;
    }

    Point operator-() {
        return {-x, -y};
    }

    Point operator-(const Point& p)
    {
        return {x - p.x, y - p.y};
    }

    Point operator-(const int n) {
        return {x - n, y - n};
    }

    Point operator/(const int n) {
        return {x / n, y / n};
    }

    Point& operator-=(const Point& p)
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point& operator-=(int n)
    {
        x -= n;
        y -= n;
        return *this;
    }

    Point& operator/=(int n) {
        x /= n;
        y /= n;
        return *this;
    }
  
    Point()
    {
        x = 0;
        y = 0;
    }

    Point(DIR dir) : Point(to_point(dir, true)) {}

    operator DIR() {return to_dir(*this);}

    Point(int x, int y)
    {
        this->x = (int16_t)x;
        this->y = (int16_t)y;
    }
    
    Point(const Pointd& p);


    static const Point UNDEF;
};
const Point Point::UNDEF = {INT16_MIN, INT16_MIN};




struct Pointd
{
    double x;
    double y;

    Pointd floor()
    {
        return {(double)(::floor(x)), (double)(::floor(y))};
    }
    
    Pointd()
    {
        x = 0;
        y = 0;
    }

    Pointd(const Point& p)
    {
        x = (double)p.x;
        y = (double)p.y;
    }

    Pointd(double x, double y)
    {
        this->x = (double)x;
        this->y = (double)y;
    }
    
    Pointd(int x, int y)
    {
        this->x = (double)x;
        this->y = (double)y;
    }
};

Point::Point(const Pointd& p)
{
    x = (int16_t)(round(p.x));
    y = (int16_t)(round(p.y));
}

Point to_point(DIR dir, bool invert_y) {
    Point ret = {0, 0};

    if      (dir == DIR::UP   ) {
        ret = { 0,  1};
    }else if(dir == DIR::DOWN ) {
        ret = { 0, -1};
    }else if(dir == DIR::LEFT ) {
        ret = {-1,  0};
    }else if(dir == DIR::RIGHT) {
        ret = { 1,  0};
    }

    if(invert_y) {
        ret.y = -ret.y;
    }

    return ret;
}

DIR to_dir(Point point, bool invert_y) {
    if(invert_y) {
        point.y = -point.y;
    }

    if      (point == Point{ 0,  1}) {
        return DIR::UP   ;
    }else if(point == Point{ 0, -1}) {
        return DIR::DOWN ;
    }else if(point == Point{-1,  0}) {
        return DIR::LEFT ;
    }else if(point == Point{ 1,  0}) {
        return DIR::RIGHT;
    }
}

std::ostream& operator<<(std::ostream& os, const Point p) {
    os << "{" << p.x << ", " << p.y << "}";
    return os;
}


/**
 * @brief rotates a point by incrememnts of 90 degrees (rotates around the origin 0,0 point)
 * @param p the point you want to rotate around the origin
 * @param rot the degrees you want rotate the point, any non 90° rotation are forbiden
 */
Point rotate90_pos(Point p, int rot, LINE_TRACKER) {
    //make sure the user inputed a multiple of a 90° angle
    if(rot % 90 != 0) {
        println(ERROR_LINE,"the rotation (rot:",rot,") inputed in ",__func__," is invalid (its not a multiple of 90)");
        return Point::UNDEF;
    }

    //get raw rotation : (0->0°, 1->90°, 2->180°, 3->270°)
    int r = MOD(rot / 90, 4);

    //every iteration of this loop, `p` gets rotated 90°, since r is the number of 90°s p will be rotated perfectly
    for(int i = 0; i < r; i++) {
        int temp = p.x; 
        p.x = p.y;
        p.y = -temp;
    }

    //return the result
    return p;
}

/**
 * @brief rotates `p` around `o` by `rot`° (`rot`° being a multiple of 90°)
 * @param p the point that is getting rotateds
 * @param o the origin point that `p` rotates around
 * @param rot the rotation in degrees that p will be rotated by (must be a multiple of 90°)
 */
Point rotate90_around(Point p, Point o, int rot, LINE_TRACKER) {
    p -= o;                                      //shift `p` by `o` so 0,0 is at the same relative position that `p` would see normally
    p = rotate90_pos(p, rot, LINE_TRACKER_INPUT);//rotate `p` around 0,0 by the desired `rot` rotation

    if(p == Point::UNDEF) return Point::UNDEF;   //early error return when rotate90_pos fails

    p += o;                                      //unshift `p` by `o`, so that p is rotated around o instead of 0,0
    return p;                                    //return the results
}


#define GRID_DIM int grid_w, int grid_h
#define GRID_INFO uint8_t* grid, GRID_DIM
#define GRID_INPUT grid, grid_w, grid_h
#define GRID_DIM_INPUT grid_w, grid_h

void set_grid(GRID_INFO, int x, int y, bool v, LINE_TRACKER) {
    int true_i = x + y * grid_w;
    
    if(true_i < 0 || grid_w * grid_h <= true_i) {
        println(ERROR_LINE,"the set grid position (",x,", ",y,") is out of bounds, here are the bounds for the grid (0-",grid_w - 1,", 0-",grid_h - 1,")");
    }
    
    int i = true_i / 8;
    int byte_i = true_i % 8;

    if(v) {
        grid[i] |=  (1 << byte_i);
    }else {
        grid[i] &= ~(1 << byte_i);
    }
}

bool get_grid(const GRID_INFO, int x, int y, LINE_TRACKER) {
    int true_i = x + y * grid_w;
    
    if(true_i >= grid_w * grid_h) {
        println(ERROR_LINE,"the get grid position (",x,", ",y,") is out of bounds, here are the bounds for the grid (0-",grid_w - 1,", 0-",grid_h - 1,")");
    }
    
    int i = true_i / 8;
    int byte_i = true_i % 8;

    bool v = grid[i] & 1 << byte_i;
    return v;
}

void print_grid(const GRID_INFO, LINE_TRACKER) {
    for(int y = 0; y < grid_h; y++) {
        for(int x = 0; x < grid_w; x++) {
            bool v = get_grid(grid, grid_w, grid_h, x, y);
            
            if(v) print("██");
            else  print("  ");
        }
        println();
    }
}

void show_pos(const GRID_INFO, Point p, LINE_TRACKER) {
    for(int y = 0; y < grid_h; y++) {
        for(int x = 0; x < grid_w; x++) {
            bool v = get_grid(grid, grid_w, grid_h, x, y);

            if(p.x == x && p.y == y) {
                if(v) print("▒▒");
                else  print("░░");
            }else {
                if(v) print("██");
                else  print("  ");
            }
        }
        println();
    }
}

void test_grid(GRID_INFO) {
    DEBUG_BANNER("before");
    print_grid(grid, grid_w, grid_h);

    int x = 5;
    int y = 4;

    DEBUG_BANNER("AT (",x,", ",y,") (should be 0)");
    bool v1 = get_grid(grid, grid_w, grid_h, x, y);
    DEBUG(v1);

    set_grid(grid, grid_w, grid_h, x, y, 1);

    DEBUG_BANNER("AT (",x,", ",y,") (should be 1)");
    bool v2 = get_grid(grid, grid_w, grid_h, x, y);
    DEBUG(v2);

    DEBUG_BANNER("after");
    print_grid(grid, grid_w, grid_h);
}

/**
 * @brief rotates a grid position `p` around the center of a hypothetical grid with dimentions `grid_w`, `grid_h` by `rot` amount of degrees (MUST BE INCREMENTS OF 90°)
 * @param p position you want to rotate
 * @param grid_w width of your hypothetical grid
 * @param grid_h height of your hypothetical grid
 * @param rot rotation in degrees (must be multiple of 90°) 
 */
Point rotate_grid_pos(GRID_DIM, Point p, int rot, LINE_TRACKER) {
    //get grid center
    Point c = {grid_w, grid_h};
    c = (c - 1) / 2;

    //rotate the point around the center of the grid
    return rotate90_around(p, c, rot, LINE_TRACKER_INPUT);
}

typedef uint8_t axis_t;
namespace AXIS {
    enum : axis_t {
        X = 0b001,
        Y = 0b010,
        Z = 0b100,
    };
};

typedef int16_t orient_t;

/**
 * @brief mirrors a point `p` in the `axes` inputed from the center of the hypothetical grid with dimententions `grid_w` and `grid_h`
 * @param p the point you want to mirror
 * @param axes the axes you want to mirror in 
 * @param grid_w width of hypothetical grid
 * @param grid_h height of hypothetical grid
 */
Point mirror_grid_pos(GRID_DIM, Point p, axis_t axes, LINE_TRACKER) {
    if(axes & AXIS::Z) {
        println(ERROR_LINE,"the axes specified containt the Z axis, this function only accepts X and Y");
        return Point::UNDEF;
    }

    //get grid center
    Point c = {grid_w, grid_h};
    c = (c - 1) / 2;

    //invert position based on the axes present
    if(axes & AXIS::X) p.x = c.x - (p.x - c.x);
    if(axes & AXIS::Y) p.y = c.y - (p.y - c.y);

    //return the new mirrored position
    return p;
}

/**
 * @brief make a mask with `len` number of bits
 * @param len the number of bits of the mask
 * @param T the type of the number you want to use the mask on
 * @param UT the unsigned type of the number (if the original type is unsigned it stays unsigned)
 */
template<typename T, typename UT = typename to_unsigned<typename raw_type<T>::type>::type>
UT create_mask(int8_t len) {
    //get the number of bits of the number
    const int n_of_bits = sizeof(T) * 8;

    //make a mask with `len` number of bits
    UT mask;
    if(len >= n_of_bits) {
        //if the len is equal to the number of bits then we should invert all the bits
        mask = ~(UT)(0);
    }else {
        //if the length is smaller than the number of bits, we can safely do bitshift math
        mask = ((UT)(1) << len) - 1;
    }
    return mask;
}

/**
 * @param n the number you want to get the bits from
 * @param i the starting index of the bits you want to take (the least significant bit is bit 1 and the most significant is bit 8)
 * @param iend the ending index of the bits you want to take (inclusively) (if left unspecified it defaults to `i`)
 * @returns the specific bits from the number n as a unsigned number
 */
template<typename T, typename UT>
UT get_bits(T n, int8_t i, int8_t iend) {
    //UT is the unsigned type of the number you want to modify

    //make a copy of the number as unsigned (we want the raw bits) 
    UT un = n;

    //iend stays same as i when its not set (default to length of 1)
    if(iend == NO_INDEX) iend = i;
    i--; iend--;

    //figure out the length of the range we want to take 
    int8_t len = iend - i + 1;
    
    //make a mask with `len` number of bits
    UT mask = create_mask<UT>(len);

    //bitshift the unsigned raw bit number by the starting index (i.e. `i`) this brings the number to the mask
    un >>= i;

    //use mask on the unsigned number to get the correct bits
    un &= mask;

    //return the result
    return un;
}

/**
 * @param n the number you want to set the bits
 * @param i the starting index of the bits you want to set (the least significant bit is bit 1 and the most significant is bit 8)
 * @param iend the ending index of the bits you want to set (inclusively) (if left unspecified it defaults to `i`)
 * @param bits the bits you want to set (as a unsigned number)
 */
template<typename T, typename UT>
void set_bits(T& n, UT bits, int8_t i, int8_t iend) {
    //iend stays same as i when its not set (default to length of 1)
    if(iend == NO_INDEX) iend = i;
    i--; iend--;

    //figure out the length of the range we want to set 
    int8_t len = iend - i + 1;
    
    //make a mask with `len` number of bits
    UT mask = create_mask<UT>(len);

    //use mask on bits (this makes sure the bits fit in between i and iend)
    bits &= mask;

    //bitshift the mask to where we want to set the bits (i.e. `i`)
    mask <<= i;

    //reset the range in the number to 0 so we can set the bits easely
    n &= ~mask;

    //set the bits
    n |= bits << i;
}


#endif//}

// network comand handle base code {
#if true
////////////////////////////////////////////////////////////////////////////////
//////////////////////// CMD_HANDLE COMPATIBILITY LAYER ////////////////////////
////////////////////////////////////////////////////////////////////////////////


#undef ERROR
#define CMD_IDS(...) \
enum CMD_ID : uint8_t { __VA_ARGS__ }; \
const char* str_ids = #__VA_ARGS__;


namespace CMD {

    //declare commands
    CMD_IDS(
        ERROR        ,
        WARNING      ,
        LOGIN        ,
        SIGNUP       ,
        PC_ID        ,
        SESS_ID      ,
        CREATE_PC_ID ,
        SET_PC_ID    ,
        SEND_TO_PC   ,
        SEND_TO_WEB  ,
        WEB_CONNECT  ,
        RTC_OFFER    ,
        RTC_ANSWER   ,
        RTC_CANDIDATE,
        GET_TURN_CRED,
    );

    std::string make_cmd(CMD_ID cmd_id, const uint8_t* data, int len) {
        int combined_len = len + 1;
        uint8_t* combined = new uint8_t[combined_len];
        combined[0] = (uint8_t)(cmd_id);
        
        //copy the data array
        for(int i = 0; i < len; i++) combined[1 + i] = data[i];//+1 for merged cmd_id at the start

        std::string output{(char*)(combined), (unsigned int)(combined_len)};
        delete[] combined;//no memory leaks

        return output;
    }
    std::string make_cmd(CMD_ID cmd_id, const char* data) {
        return make_cmd(cmd_id, (const uint8_t*)(data), strlen_tk(data));
    }
    std::string make_cmd(CMD_ID cmd_id, std::string data) {
        return make_cmd(cmd_id, (const uint8_t*)(data.c_str()), data.length());
    }

    /**
     * @brief used to search for a specifc setting's value within a string 
     * 
     * e.g. in the following example data `"example_sett:value"` the example_sett could be found by inputing `"example_sett:"` in the `setting` argument
     * 
     * @note the data settings are found by matching your exact setting string at the start of the line, the rest of the line is the value
     * 
     * e.g. in the following example
     * 
     * ```txt
     * example_sett_long_name:value\n
     * ^~~~~~~~~~~~~~~~~~~~~~~
     * searches for this      ^~~~~
     *                        the value you obtain
     * ```
     * 
     * @return returns a struct containing index (starting index of value) and length of value within the specified data
     */
    Parser::Arg get_data_setting(const uint8_t* data, int len        , const char* setting, int sett_len, FND = FND(), int search_start_i = 0) {
        const char* datastr = (const char*)(data);

        //find the settings
        int sett_i_start = findstr(datastr, len, setting, sett_len, search_start_i, 0, 0, 0, "\n", 0);

        //if we didn't find the settings
        if(sett_i_start == -1) {
            return Parser::Arg::UNDEF;
        }else {
            sett_i_start += sett_len;//skip the setting we specified within the input
        }

        int sett_i_end   = 0;

        //find the next new line or the end of the string
        for(int i = sett_i_start;; i++) {
            if(i >= len || datastr[i] == '\n') {
                sett_i_end = i - 1;
                break;
            }
        }

        Parser::Arg output = {sett_i_start, sett_i_end - sett_i_start + 1};
        return output;
    }
    Parser::Arg get_data_setting(const uint8_t* data, int len        , const char* setting,               FND = FND(), int search_start_i = 0) {
        int sett_len = strlen_tk(setting);
        return get_data_setting(data, len, setting, sett_len, FND(), search_start_i);
    }
    Parser::Arg get_data_setting(const uint8_t* data, Parser::Arg arg, const char* setting, int sett_len, FND = FND(), int search_start_i = 0) {
        return get_data_setting(data + arg.i, arg.len, setting, sett_len, FND(), search_start_i);
    }
    Parser::Arg get_data_setting(const uint8_t* data, Parser::Arg arg, const char* setting,               FND = FND(), int search_start_i = 0) {
        int sett_len = strlen_tk(setting);
        return get_data_setting(data + arg.i, arg.len, setting, sett_len, FND(), search_start_i);
    }
    Parser::Arg get_data_setting(const char*    data, Parser::Arg arg, const char* setting,               FND = FND(), int search_start_i = 0) {
        int sett_len = strlen_tk(setting);
        return get_data_setting((const uint8_t*)(data) + arg.i, arg.len, setting, sett_len, FND(), search_start_i);
    }
    Parser::Arg get_data_setting(std::string    data, Parser::Arg arg, const char* setting,               FND = FND(), int search_start_i = 0) {
        int sett_len = strlen_tk(setting);
        return get_data_setting((const uint8_t*)(data.c_str()) + arg.i, arg.len, setting, sett_len, FND(), search_start_i);
    }

    const static int max_data_settings = 15;
    Parser::Arg data_settings[max_data_settings];
    Parser::Args get_data_settings(const uint8_t* data, int len        , const char* setting, int sett_len, LINE_TRACKER) {
        //repeatly call get_data_setting to get all data settings
        int last_search_index = 0;
        int n_of_sett         = 0;
        while(true) {
            //search from the last_search_index
            Parser::Arg curr_sett = get_data_setting(data, len, setting, sett_len, FND(), last_search_index);
            
            //leave if the setting wasn't found
            if(curr_sett == Parser::Arg::UNDEF) break;
            
            //add setting to the list
            if(n_of_sett < max_data_settings) {
                data_settings[n_of_sett] = curr_sett;
                n_of_sett++;
            }else {
                println("ERROR line ",line," in ",file," in ",__func__,"(...) function, the number of data settings found exceeded the storage set (max of ",max_data_settings," data settings");
                for(int i = 0; i < n_of_sett; i++) {
                    Parser::Arg data_sett = data_settings[i];
                    display_info((const char*)(data), data_sett, 0, 1);
                    println("[setting ",i,"]");
                }

                //early return bcs cannot store enough settings
                return {data_settings, n_of_sett};
            }

            //update the last search index, so next search skips the one we just did
            last_search_index = curr_sett.i + curr_sett.len + 1; //this will leave the index right after the \n of the setting

            //if the new index is out of bounds then get ouf of the loop (equivalent of Parser::Arg::UNDEF)
            if(last_search_index >= len) break;
        }

        //return the settings
        return {data_settings, n_of_sett};
    }
    Parser::Args get_data_settings(const uint8_t* data, int len        , const char* setting,               LINE_TRACKER) {
        int sett_len = strlen_tk(setting);
        return get_data_settings(data, len, setting, sett_len, FND(), line, file);
    }
    Parser::Args get_data_settings(const char*    data,                  const char* setting,               LINE_TRACKER) {
        return get_data_settings((const uint8_t*)(data), strlen_tk(data), setting, strlen_tk(setting), FND(), line, file);
    }
    Parser::Args get_data_settings(const char*    data, int len        , const char* setting,               LINE_TRACKER) {
        return get_data_settings((const uint8_t*)(data), len, setting, strlen_tk(setting), FND(), line, file);
    }
    Parser::Args get_data_settings(const char*    data, int len        , const char* setting, int sett_len, LINE_TRACKER) {
        return get_data_settings((const uint8_t*)(data), len, setting, sett_len, FND(), line, file);
    }
    Parser::Args get_data_settings(const uint8_t* data, Parser::Arg arg, const char* setting, int sett_len, LINE_TRACKER) {
        return get_data_settings(data + arg.i, arg.len, setting, sett_len, FND(), line, file);
    }
    Parser::Args get_data_settings(const uint8_t* data, Parser::Arg arg, const char* setting,               LINE_TRACKER) {
        int sett_len = strlen_tk(setting);
        return get_data_settings(data + arg.i, arg.len, setting, sett_len, FND(), line, file);
    }
    Parser::Args get_data_settings(const char*    data, Parser::Arg arg, const char* setting,               LINE_TRACKER) {
        int sett_len = strlen_tk(setting);
        return get_data_settings((const uint8_t*)(data) + arg.i, arg.len, setting, sett_len, FND(), line, file);
    }
    Parser::Args get_data_settings(std::string    data, Parser::Arg arg, const char* setting,               LINE_TRACKER) {
        int sett_len = strlen_tk(setting);
        return get_data_settings((const uint8_t*)(data.c_str()) + arg.i, arg.len, setting, sett_len, FND(), line, file);
    }

    //handle for struct printing when using iostream
    std::ostream& operator<<(std::ostream& os, const CMD_ID id) {
        const int str_ids_len = strlen_tk(str_ids);

        int find_count = 0;
        int i    = -1; 
        int last = -1;
        
        //while the find count (the number of commas found) is smaller than the id number and the find
        while(true) {
            int found_comma = -1;
            if(i + 1 < str_ids_len) {
                found_comma = findstr(str_ids, ",", i + 1);//store current comma
            }

            //if we didn't find anything (meaning we didn't find the id)
            if(found_comma == -1) {
                //print inexistent id to signify this
                os << "InexistentID";
                return os;
            }else {
                //otherwise, we did find a comma
                find_count++;//incrase find count (we found a comma)
                
                //set i and last based on comma we just found (i is the current comma, and last is the last comma (i.e. the last i))
                last = i;
                i = found_comma;
            }

            //if the number of commas found (i.e. `find_count`) - 1 is equal to id, then get out (means we found the correct i and last commas)
            if(find_count - 1 >= (int)(id)) break;
        }

        //get start and end of correct CMD ID (includes whitespaces)
        int start = last + 1;
        int end   = i - 1   ;

        //skip whitespace characters
        while(str_ids[start] == ' ' || str_ids[start] == '\n' || str_ids[start] == '\t') start++;
        while(str_ids[end  ] == ' ' || str_ids[end  ] == '\n' || str_ids[end  ] == '\t') end  --;

        //print the CMD ID
        const char* str = str_ids + start;
        int         len = end - start + 1;
        for(int i = 0; i < len; i++)
        {
            os << str[i];
        }

        return os;
    }
};



////////////////////////////////////////////////////////////////////////////////
//////////////////////// CMD_HANDLE COMPATIBILITY LAYER ////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif//}

// regex shenanigans {
#if true 
///* FUNCTION FINDER REGEX COMMAND *///
/*
iteration number 1: WindowProc\s*\((?:[^\)]|\n)*\)(?:[^\{]|\n)*\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:\{(?:(?:[^\{\}]|\n)*(?:\{(?:[^\}]|\n)*\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}[^\{\}]*)*)\}|\n)*\}[^\{\}]*)*)\}[^\{\}]*)*)\}
*/
/*

steps in this function : 

this gets "{" up to a "}", it does not care if there is a "{" in the way of this
\{(?:[^\}]|\n)*\}

then we recursively add a "{...}" handler inside of where the [^\}] was to make sure that we don't pass a "{" accidentally
*/


///* TEMPORARY DEBUG CLEANUM REGEX COMMAND (TEMP DEBUG REMOVE) *///
/*
iteration number 1: (?:(?:\/\/)|(?:\/\*)) ?temp debug ?:? ?(?:\*\/)?(?:(?!\n\s*\n\s|\n\s*\})(?:\n|.))*\n\s*\n\s*
iteration number 2: [ \t]*(?:(?:\/\/)|(?:\/\*)) ?temp debug ?:? ?(?:\*\/)?(?:(?!\n\s*\n\s|\n\s*\})(?:\n|.))*\n([ \t]*)(?:\n[ \t]*)?
iteration number 3: (?:\n[ \t]*)?(?:\n[ \t]*)?(?:(?:\/\/)|(?:\/\*)) ?temp debug ?:? ?(?:\*\/)?(?:(?!\n[ \t]*(?:\n[ \t]*|\}))(?:.|\n))*
*/
/*
steps in this fucntion : 

get up to two new lines in front of temp debug kewords
(?:\n[ \t]*)?(?:\n[ \t]*)?

find any kind of variation of the temp debug keyword
(?:(?:\/\/)|(?:\/\*)) ?temp debug ?:? ?(?:\*\/)?

go forward until you find either a new line or }
(?:(?!\n[ \t]*(?:\n[ \t]*|\}))(?:.|\n))*
*/
#endif//}

#endif//}