#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define NAME_LENGTH 256

int main(void) {
  char in_file[NAME_LENGTH], out_file[NAME_LENGTH];
  int in_fd, out_fd;
  ssize_t bytes_read, bytes_written;
  char buffer[BUFFER_SIZE];

  // Prompt user for source file name
  printf("Enter source file name: ");
  scanf("%s", in_file);

  // Open source file for reading
  in_fd = open(in_file, O_RDONLY);
  if (in_fd == -1) {
    perror("Cannot open source file for reading");
    close(in_fd); // Close the input file before exiting
    return EXIT_FAILURE;
  }

  // Prompt user for destination file name
  printf("Enter destination file name: ");
  scanf("%s", out_file);

  // Open destination file for writing (create it if it doesn't exist)
  out_fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (out_fd == -1) {
    perror("Cannot open destination file for writing");
    close(out_fd); // Close the output file before exiting
    return EXIT_FAILURE;
  }

  // Copy data from source to destination
  while ((bytes_read = read(in_fd, buffer, sizeof(buffer))) > 0) {
    bytes_written = write(out_fd, buffer, bytes_read);
    if (bytes_written != bytes_read) {
      perror("Error writing to destination file");
      close(in_fd);
      close(out_fd);
      return EXIT_FAILURE;
    }
  }

  // Check for read error
  if (bytes_read == -1) {
    perror("Error reading from source file");
  }

  // Close the files
  close(in_fd);
  close(out_fd);

  printf("File copied successfully!\n");
  return EXIT_SUCCESS;
}
