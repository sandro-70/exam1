/*#ifndef INVALIDRATEEXCEPTION_H
#define INVALIDRATEEXCEPTION_H

#include <exception> // Include necessary headers

class InvalidRateException : public std::exception {
public:
    // Constructor that receives the invalid rate
    InvalidRateException(int rate);

    // Override the what() function to provide a description of the exception
    const char* what() const noexcept override;

private:
    int m_rate; // Store the invalid rate
};

#endif // INVALIDRATEEXCEPTION_H
*/
