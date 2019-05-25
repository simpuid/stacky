#include <token.hpp>
ostream &operator<<(ostream &out, const Token &token)
{
    return out << token.data << string(" line:") << to_string(token.line)<<string(" column:") << to_string(token.column);
}
