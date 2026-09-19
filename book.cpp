/*==============================================================================
 *  文件名称：Book.cpp
 *  项目名称：图书馆借阅管理系统 —— 实验一：类与对象
 *  文件职责：Book 类中各成员函数的【定义（实现）】
 *
 *  说明：类的声明在 Book.h 中，本文件只写实现，所以必须包含 Book.h。
 *        main.cpp 中不出现任何成员函数的实现，
 *        满足要求 2（1）“类的声明、定义、对象生成在不同的文件里”。
 *============================================================================*/
#include "Book.h"

#include <stdexcept>        // std::invalid_argument

/*==============================================================================
 *  匿名命名空间：下面这些函数只在本 .cpp 文件内部可用，
 *  相当于“文件私有的辅助函数”，不会污染全局名字空间，
 *  也不会和其他文件中的同名函数冲突。
 *============================================================================*/
namespace {

// 默认构造函数使用的初始值（保证默认构造出来的对象也是一本“合法”的图书）
const std::string kDefaultName      = "未命名图书";
const std::string kDefaultIsbn      = "978-7-111-40701-0";   // 校验位正确的示例 ISBN
const std::string kDefaultPublisher = "未知出版社";
const double      kDefaultPrice     = 0.0;
const int         kDefaultPages     = 1;

// 判断字符串是否全部由数字字符组成
bool isAllDigits(const std::string& text)
{
    if (text.empty()) {
        return false;
    }
    for (std::size_t i = 0; i < text.size(); ++i) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }
    return true;
}

// 去掉 ISBN 中的连字符 '-' 和空格，并把小写 x 统一成大写 X
std::string normalizeIsbn(const std::string& isbn)
{
    std::string result;
    for (std::size_t i = 0; i < isbn.size(); ++i) {
        char ch = isbn[i];
        if (ch == '-' || ch == ' ') {
            continue;                   // 连字符和空格不参与校验计算
        }
        if (ch == 'x') {
            ch = 'X';                   // ISBN-10 的校验位可能写成 X（代表 10）
        }
        result.push_back(ch);
    }
    return result;
}

// 去掉字符串首尾的空白字符（空格、制表符、回车换行）
std::string trim(const std::string& text)
{
    const std::string blank = " \t\r\n";
    const std::size_t first = text.find_first_not_of(blank);
    if (first == std::string::npos) {
        return std::string();           // 整个字符串都是空白，返回空串
    }
    const std::size_t last = text.find_last_not_of(blank);
    return text.substr(first, last - first + 1);
}

} // namespace

/*==============================================================================
 *  一、初始化（构造函数）
 *============================================================================*/

// 默认构造函数：把数据成员初始化为一定的值
Book::Book()
    : m_name(kDefaultName)
    , m_isbn(kDefaultIsbn)
    , m_publisher(kDefaultPublisher)
    , m_price(kDefaultPrice)
    , m_pages(kDefaultPages)
    , m_available(true)
{
}

// 重载构造函数：用调用者给定的参数构造对象
// 构造过程中同样做合法性验证：只要有一项数据不合法就抛出异常，
// 从而保证“程序中不会存在数据不合法的 Book 对象”。
Book::Book(const std::string& name,
           const std::string& isbn,
           const std::string& publisher,
           double             price,
           int                pages,
           bool               available)
    : m_name(kDefaultName)              // 先用默认值初始化，再用 set 函数验证并赋值
    , m_isbn(kDefaultIsbn)
    , m_publisher(kDefaultPublisher)
    , m_price(kDefaultPrice)
    , m_pages(kDefaultPages)
    , m_available(true)
{
    if (!setName(name)) {
        throw std::invalid_argument("图书名称不能为空！");
    }
    if (!setIsbn(isbn)) {
        throw std::invalid_argument("ISBN 号不合法：" + isbn +
                                    "（应为 10 位或 13 位，且校验位正确）");
    }
    if (!setPublisher(publisher)) {
        throw std::invalid_argument("出版社信息不能为空！");
    }
    if (!setPrice(price)) {
        throw std::invalid_argument("价格不能为负数！");
    }
    if (!setPages(pages)) {
        throw std::invalid_argument("页数必须为正整数！");
    }
    setAvailable(available);
}

/*==============================================================================
 *  二、修改（带合法性验证）
 *============================================================================*/

bool Book::setName(const std::string& name)
{
    const std::string value = trim(name);
    if (value.empty()) {                    // 验证：图书名称不能为空
        return false;
    }
    m_name = value;
    return true;
}

bool Book::setIsbn(const std::string& isbn)
{
    if (!isValidIsbn(isbn)) {               // 验证：ISBN 必须通过校验位算法
        return false;
    }
    m_isbn = trim(isbn);
    return true;
}

bool Book::setPublisher(const std::string& publisher)
{
    const std::string value = trim(publisher);
    if (value.empty()) {                    // 验证：出版社信息不能为空
        return false;
    }
    m_publisher = value;
    return true;
}

bool Book::setPrice(double price)
{
    if (!(price >= 0.0)) {                  // 验证：价格不能为负
        return false;                       // （写成 !(price >= 0) 可同时排除 NaN）
    }
    m_price = price;
    return true;
}

bool Book::setPages(int pages)
{
    if (pages <= 0) {                       // 验证：页数必须是正整数
        return false;
    }
    m_pages = pages;
    return true;
}

void Book::setAvailable(bool available)
{
    m_available = available;                // 布尔量只有两种取值，不需要验证
}

/*==============================================================================
 *  三、获取
 *============================================================================*/

const std::string& Book::getName() const
{
    return m_name;
}

const std::string& Book::getIsbn() const
{
    return m_isbn;
}

const std::string& Book::getPublisher() const
{
    return m_publisher;
}

double Book::getPrice() const
{
    return m_price;
}

int Book::getPages() const
{
    return m_pages;
}

bool Book::isAvailable() const
{
    return m_available;
}

/*==============================================================================
 *  四、输出
 *============================================================================*/

// 多行格式输出一本书的全部信息
void Book::print(std::ostream& os) const
{
    os << "----------------------------------------------\n"
       << "  图书名称 : " << m_name << "\n"
       << "  ISBN 号  : " << m_isbn << "\n"
       << "  出版社   : " << m_publisher << "\n"
       << "  价格     : " << m_price << " 元\n"
       << "  页数     : " << m_pages << " 页\n"
       << "  在馆状态 : " << (m_available ? "可借" : "不可借（已借出）") << "\n"
       << "----------------------------------------------\n";
}

// 运算符重载：一行显示一本书的摘要信息，方便用 cout << book 输出
std::ostream& operator<<(std::ostream& os, const Book& book)
{
    os << "《" << book.m_name << "》"
       << "  ISBN:" << book.m_isbn
       << "  出版社:" << book.m_publisher
       << "  价格:" << book.m_price << "元"
       << "  页数:" << book.m_pages << "页"
       << "  [" << (book.m_available ? "可借" : "不可借") << "]";
    return os;
}

/*==============================================================================
 *  五、其他操作
 *============================================================================*/

// 验证图书 ISBN 号的合法性（要求 1 中明确要求的“其他操作”）
//    ISBN-10：共 10 位，前 9 位是数字，最后一位是数字或 X；
//             校验规则 —— 各位加权和（权值依次为 10,9,...,2,1）能被 11 整除。
//    ISBN-13：共 13 位，全部是数字；
//             校验规则 —— 从左到右交替乘以 1、3 的加权和能被 10 整除。
//    输入中允许出现连字符和空格（计算前先去掉）。
bool Book::isValidIsbn(const std::string& isbn)
{
    const std::string code = normalizeIsbn(isbn);   // 先去掉连字符和空格

    // ------------------------- ISBN-10 -------------------------
    if (code.size() == 10) {
        if (!isAllDigits(code.substr(0, 9))) {      // 前 9 位必须都是数字
            return false;
        }
        const char last = code[9];                  // 第 10 位是校验位
        if (!(last >= '0' && last <= '9') && last != 'X') {
            return false;                           // 校验位只能是数字或 X
        }
        int sum = 0;
        for (int i = 0; i < 9; ++i) {
            sum += (10 - i) * (code[i] - '0');      // 权值 10,9,...,2
        }
        sum += (last == 'X') ? 10 : (last - '0');   // 权值 1
        return (sum % 11) == 0;
    }

    // ------------------------- ISBN-13 -------------------------
    if (code.size() == 13) {
        if (!isAllDigits(code)) {                   // 13 位必须全部是数字
            return false;
        }
        int sum = 0;
        for (int i = 0; i < 13; ++i) {
            const int digit = code[i] - '0';
            sum += (i % 2 == 0) ? digit : digit * 3;    // 奇数位乘 3
        }
        return (sum % 10) == 0;
    }

    return false;                                   // 其他长度一律不合法
}

// 借出图书：只有在馆（可借）状态才能借出，成功返回 true
bool Book::borrowBook()
{
    if (!m_available) {             // 状态验证：已经借出去的书不能再借
        return false;
    }
    m_available = false;            // 借出后，在馆状态发生改变
    return true;
}

// 归还图书：只有已借出（不可借）状态才需要归还，成功返回 true
bool Book::returnBook()
{
    if (m_available) {              // 本来就在馆的书不需要归还
        return false;
    }
    m_available = true;             // 归还后，在馆状态发生改变
    return true;
}
