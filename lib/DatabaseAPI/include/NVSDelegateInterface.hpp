#ifndef NVS_DELEGATE_INTERFACE_H
#define NVS_DELEGATE_INTERFACE_H

#include <stdint.h>
#include <stddef.h>

#define NVS_DELEGATE_MAX_KEY_LENGTH 16
#define NVS_DELEGATE_MAX_VALUE_LENGTH 4096
#define NVS_DELEGATE_MAX_NAMESPACE_LENGTH 16

/**
 * @brief Enumeration representing possible errors during NVS (Non-Volatile Storage) operations.
 */
enum NVSDelegateError_t : uint8_t
{
    NVS_DELEGATE_OK,                 ///< Operation successful.
    NVS_DELEGATE_KEY_INVALID,        ///< Invalid key.
    NVS_DELEGATE_VALUE_INVALID,      ///< Invalid value.
    NVS_DELEGATE_NAMESPACE_INVALID,  ///< Invalid namespace name.
    NVS_DELEGATE_KEY_NOT_FOUND,      ///< Key not found.
    NVS_DELEGATE_NOT_ENOUGH_SPACE,   ///< Not enough space in the storage.
    NVS_DELEGATE_HANDLE_INVALID,     ///< Invalid namespace handle.
    NVS_DELEGATE_READONLY,           ///< Attempt to modify in READONLY mode.
    NVS_DELEGATE_KEY_ALREADY_EXISTS, ///< Key already exists.
    NVS_DELEGATE_UNKOWN_ERROR        ///< Unknown error.
};

/**
 * @brief Enumeration representing the mode in which a namespace is opened.
 */
enum class NVSDelegateOpenMode_t : uint8_t
{
    NVSDelegate_READWRITE, ///< Read-Write mode.
    NVSDelegate_READONLY   ///< Read-Only mode.
};

/**
 * @brief Type definition for a handle representing a non-volatile storage namespace.
 */
typedef uint32_t NVSDelegateHandle_t;

/**
 * @brief Interface for non-volatile storage operations.
 */
class NVSDelegateInterface
{
public:
    /**
     * @brief Virtual destructor for NVSDelegateInterface.
     */
    virtual ~NVSDelegateInterface() = default;

    /**
     * @brief Opens a namespace in non-volatile storage with the specified name and mode.
     *
     * @param name The name of the namespace to open.
     * @param open_mode The mode in which to open the namespace (READWRITE or READONLY).
     * @param out_handle Pointer to receive the handle for the opened namespace.
     * @return NVSDelegateError_t indicating the success or failure of the operation.
     *         - NVS_DELEGATE_OK: Operation successful.
     *         - NVS_DELEGATE_NAMESPACE_INVALID: Invalid namespace name.
     *         - NVS_DELEGATE_NOT_ENOUGH_SPACE: Not enough space in the storage.
     *         - NVS_DELEGATE_KEY_NOT_FOUND: Namespace not found.
     *         - NVS_DELEGATE_UNKOWN_ERROR: Unknown error.
     */
    virtual NVSDelegateError_t open(
        char const *const name, NVSDelegateOpenMode_t const open_mode,
        NVSDelegateHandle_t *out_handle) const = 0;

    /**
     * @brief Closes the specified non-volatile storage namespace.
     *
     * @param handle The handle of the namespace to close.
     */
    virtual void close(NVSDelegateHandle_t handle) const = 0;

    /**
     * @brief Sets a string value for the specified key in the given non-volatile storage namespace.
     *
     * @param handle The handle of the namespace.
     * @param key The key for the string value.
     * @param value The string value to set.
     * @return NVSDelegateError_t indicating the success or failure of the operation.
     *         - NVS_DELEGATE_OK: Operation successful.
     *         - NVS_DELEGATE_KEY_INVALID: Invalid key.
     *         - NVS_DELEGATE_VALUE_INVALID: Invalid value.
     *         - NVS_DELEGATE_READONLY: Attempt to write in READONLY mode.
     *         - NVS_DELEGATE_NOT_ENOUGH_SPACE: Not enough space in the storage.
     *         - NVS_DELEGATE_HANDLE_INVALID: Invalid namespace handle.
     *         - NVS_DELEGATE_UNKOWN_ERROR: Unknown error.
     */
    virtual NVSDelegateError_t set_str(
        NVSDelegateHandle_t handle, char const *const key,
        char const *const value) const = 0;

    /**
     * @brief Gets the string value for the specified key from the given non-volatile storage namespace.
     *
     * @param handle The handle of the namespace.
     * @param key The key for the string value.
     * @param out_value Buffer to store the retrieved string value.
     * @param length Pointer to the length of the buffer; updated with the actual length of the string.
     * @return NVSDelegateError_t indicating the success or failure of the operation.
     *         - NVS_DELEGATE_OK: Operation successful.
     *         - NVS_DELEGATE_KEY_INVALID: Invalid key.
     *         - NVS_DELEGATE_VALUE_INVALID: Invalid value.
     *         - NVS_DELEGATE_HANDLE_INVALID: Invalid namespace handle.
     *         - NVS_DELEGATE_KEY_NOT_FOUND: Key not found.
     *         - NVS_DELEGATE_UNKOWN_ERROR: Unknown error.
     */
    virtual NVSDelegateError_t get_str(
        NVSDelegateHandle_t handle, char const *const key,
        char *out_value, size_t *length) const = 0;

    /**
     * @brief Erases the key and its associated value from the specified non-volatile storage namespace.
     *
     * @param handle The handle of the namespace.
     * @param key The key to erase.
     * @return NVSDelegateError_t indicating the success or failure of the operation.
     *         - NVS_DELEGATE_OK: Operation successful.
     *         - NVS_DELEGATE_KEY_INVALID: Invalid key.
     *         - NVS_DELEGATE_HANDLE_INVALID: Invalid namespace handle.
     *         - NVS_DELEGATE_KEY_NOT_FOUND: Key not found.
     *         - NVS_DELEGATE_READONLY: Attempt to erase in READONLY mode.
     *         - NVS_DELEGATE_UNKOWN_ERROR: Unknown error.
     */
    virtual NVSDelegateError_t erase_key(
        NVSDelegateHandle_t handle, char const *const key) const = 0;

    /**
     * @brief Erases all keys and values from the specified non-volatile storage namespace.
     *
     * @param handle The handle of the namespace.
     * @return NVSDelegateError_t indicating the success or failure of the operation.
     *         - NVS_DELEGATE_OK: Operation successful.
     *         - NVS_DELEGATE_HANDLE_INVALID: Invalid namespace handle.
     *         - NVS_DELEGATE_READONLY: Attempt to erase in READONLY mode.
     *         - NVS_DELEGATE_UNKOWN_ERROR: Unknown error.
     */
    virtual NVSDelegateError_t erase_all(NVSDelegateHandle_t handle) const = 0;

    /**
     * @brief Erases all keys and values from all non-volatile storage namespaces.
     *
     * @return NVSDelegateError_t indicating the success or failure of the operation.
     *         - NVS_DELEGATE_OK: Operation successful.
     *         - NVS_DELEGATE_UNKOWN_ERROR: Unknown error.
     */
    virtual NVSDelegateError_t erase_flash_all() const = 0;

    /**
     * @brief Commits any pending changes to the specified non-volatile storage namespace.
     *
     * @param handle The handle of the namespace.
     * @return NVSDelegateError_t indicating the success or failure of the operation.
     *         - NVS_DELEGATE_OK: Operation successful.
     *         - NVS_DELEGATE_HANDLE_INVALID: Invalid namespace handle.
     *         - NVS_DELEGATE_READONLY: Attempt to commit in READONLY mode.
     *         - NVS_DELEGATE_UNKOWN_ERROR: Unknown error.
     */
    virtual NVSDelegateError_t commit(NVSDelegateHandle_t handle) const = 0;
};

#endif // NVS_DELEGATE_INTERFACE_H
