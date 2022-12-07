#ifndef _AOC_INCLUDE_H_
#define _AOC_INCLUDE_H_

#include <string>
#include <string_view>
#include <vector>

struct File
{
  std::string name;
  std::size_t size = 0;
};

struct Directory
{
  std::string name;
  Directory* pParent = nullptr;
  std::vector<Directory> subDirectories;
  std::vector<File> files;
};

class FileSystem
{
public:
  void AddDirectory(std::string_view name);
  void AddFile(std::string_view name, std::size_t size);

  bool HasDirectory(std::string_view name) const;
  bool HasFile(std::string_view name) const;

  void ChangeDirectory(std::string_view newDir);

  std::size_t GetDirectorySize(Directory const* pDir = nullptr) const;

  std::vector<Directory const*> GetDirectories(Directory const* pStart = nullptr) const;
  std::vector<File const*> GetFiles(Directory const* pStart = nullptr) const;

private:
  Directory root{"/"};
  Directory* cwd = &root;
};

class CommandParser
{
public:
  enum class Commands {NONE, CD, LS};
  void ParseLine(std::string_view line);

  std::size_t GetDirectorySize(Directory const* pDir = nullptr) const;

  std::vector<Directory const*> GetDirectories(Directory const* pStart = nullptr) const;
  std::vector<File const*> GetFiles() const;

private:
  Commands currentCommand = Commands::NONE;
  FileSystem fileSystem;
};

#endif