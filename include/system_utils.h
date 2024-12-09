/**
 * @file system_utils.h
 * @brief System-specific utility functions
 *
 * Provides platform-independent implementations of system
 * utilities like screen clearing.
 */

#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

/**
 * @brief Clears the terminal screen
 * 
 * Uses platform-specific methods to clear the screen:
 * - Windows: Uses console API
 * - Unix: Uses ANSI escape codes or system command
 */
void clear_screen(void);

#endif // SYSTEM_UTILS_H 