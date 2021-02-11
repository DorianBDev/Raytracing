#ifndef H_RAYTRACING_EXCEPTIONS_H
#define H_RAYTRACING_EXCEPTIONS_H

#include <stdexcept>
#include <string>
#include <utility>

namespace Exception
{
    /**
     * @brief Base class for the project exceptions.
     */
    class RaytracingException : public std::runtime_error
    {
    public:
        /**
         * @brief Create a raytracing exception.
         *
         * @param prefix  The prefix to use.
         * @param message The message to use.
         *
         * The final from will be "[prefix] message".
         */
        explicit RaytracingException(std::string prefix, std::string message);

        /**
         * @brief Create a raytracing exception.
         *
         * @param prefix           The prefix to use.
         * @param message          The message to use.
         * @param secondaryMessage The secondary message.
         *
         * The final from will be "[prefix] message. -- secondary message.".
         */
        explicit RaytracingException(std::string prefix, std::string message, std::string secondaryMessage);

        /**
         * @brief Get the origin of the exception, as a message.
         *
         * @return Returns the origin of the exception (char*).
         */
        const char* what() const noexcept override
        {
            return m_what.c_str();
        }

    private:
        std::string m_prefix;
        std::string m_message;
        std::string m_secondaryMessage;
        std::string m_what;
    };

    /////////////////////////////////////////////////////////////////////
    /// Matrix
    /////////////////////////////////////////////////////////////////////

    namespace Matrix
    {
        /**
         * @brief Used when the matrix is of a wrong size (like for matrix product).
         */
        class WrongSize : public RaytracingException
        {
        public:
            explicit WrongSize(std::string secondaryMessage = "")
                : RaytracingException("MATRIX", "Wrong matrix size.", std::move(secondaryMessage)){};
        };

        /**
         * @brief Used when the coordinates are wrong when accessing a matrix.
         */
        class WrongCoordinates : public RaytracingException
        {
        public:
            explicit WrongCoordinates(std::string secondaryMessage = "")
                : RaytracingException("MATRIX",
                                      "Wrong coordinates when accessing a matrix.",
                                      std::move(secondaryMessage)){};
        };

        /**
         * @brief Used when trying to use a matrix that isn't initialized.
         */
        class NotInitialized : public RaytracingException
        {
        public:
            explicit NotInitialized(std::string secondaryMessage = "")
                : RaytracingException("MATRIX", "The matrix isn't initialized.", std::move(secondaryMessage)){};
        };

        /**
         * @brief Used when trying to create a vector3 from a matrix with the wrong shape (!= (1,3)).
         */
        class NotVector3 : public RaytracingException
        {
        public:
            explicit NotVector3(std::string secondaryMessage = "")
                : RaytracingException("MATRIX",
                                      "The matrix isn't a vector3 (!= (1,3)).",
                                      std::move(secondaryMessage)){};
        };

        /**
         * @brief Used when matrices are not of the same size, and that's needed.
         */
        class NotSameSize : public RaytracingException
        {
        public:
            explicit NotSameSize(std::string secondaryMessage = "")
                : RaytracingException("MATRIX", "Matrices are not of the same size.", std::move(secondaryMessage)){};
        };

        /**
         * @brief Used when matrices have wrong sizes to do a matrix product.
         */
        class WrongSizesForProduct : public RaytracingException
        {
        public:
            explicit WrongSizesForProduct(std::string secondaryMessage = "")
                : RaytracingException("MATRIX",
                                      "Wrong matrix size to make a matrix product.",
                                      std::move(secondaryMessage)){};
        };

        /**
         * @brief Used when initializer list is wrong.
         */
        class WrongInitializerList : public RaytracingException
        {
        public:
            explicit WrongInitializerList(std::string secondaryMessage = "")
                : RaytracingException("MATRIX", "Wrong matrix initializer list.", std::move(secondaryMessage)){};
        };

        /**
         * @brief Used when a matrix is not invertible.
         */
        class NotInvertible : public RaytracingException
        {
        public:
            explicit NotInvertible(std::string secondaryMessage = "")
                : RaytracingException("MATRIX", "The matrix is not invertible", std::move(secondaryMessage)){};
        };
    } // namespace Matrix

    /////////////////////////////////////////////////////////////////////
    /// Vector3
    /////////////////////////////////////////////////////////////////////

    namespace Vector3
    {
        /**
         * @brief Used when initializer list is wrong.
         */
        class WrongInitializerList : public RaytracingException
        {
        public:
            explicit WrongInitializerList(std::string secondaryMessage = "")
                : RaytracingException("VECTOR3", "Wrong Vector3 initializer list.", std::move(secondaryMessage)){};
        };
    } // namespace Vector3

    /////////////////////////////////////////////////////////////////////
    /// Math
    /////////////////////////////////////////////////////////////////////

    namespace Math
    {
        /**
         * @brief Used when initializer list is wrong.
         */
        class DivisionByZero : public RaytracingException
        {
        public:
            explicit DivisionByZero(std::string secondaryMessage = "")
                : RaytracingException("MATH", "Division by 0.", std::move(secondaryMessage)){};
        };
    } // namespace Math
} // namespace Exception

#endif //H_RAYTRACING_EXCEPTIONS_H
