#ifndef AIC19_CLIENT_CPP_FILE_DESCRIPTOR_H
#define AIC19_CLIENT_CPP_FILE_DESCRIPTOR_H

/**
 * An RAII wrapper for unix file descriptors
 */
class FileDescriptor final {
public:

    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator= (const FileDescriptor&) = delete;

    /**
     * Constructor
     */
    explicit FileDescriptor(int fd = -1) noexcept;

    /**
     * Move constructor
     */
    FileDescriptor(FileDescriptor&& rhs) noexcept;

    /**
     * Move assignment operator
     */
    FileDescriptor& operator= (FileDescriptor&& rhs) noexcept;

    /**
     * Destructor
     */
    ~FileDescriptor() noexcept;

    /**
     * Reset the file descriptor
     *
     * This function closes the previously held resource (if any) and takes ownership of the file descriptor passed in
     * as parameter.
     *
     * @param fd The new file descriptor to hold
     */
    void reset(int fd = -1);

    /**
     * Release the ownership of currently held resource and return it
     *
     * @return The currently held file descriptor
     */
    int release();

    /**
     * @return A copy of currently held resource
     */
    int get() const;

    /**
     * Boolean conversion operator
     *
     * @return True if this object is managing a resource, false otherwise
     */
    explicit operator bool() const;

private:

    /// The current file descriptor held by this class
    int m_fd;
};

#endif // AIC19_CLIENT_CPP_FILE_DESCRIPTOR_H
