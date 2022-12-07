#include "include.h"
#include <cctype>
#include <sstream>

namespace Util
{
  // Split based on white space
  std::vector<std::string_view> Split(std::string_view line)
  {
    std::vector<std::string_view> output;
    std::size_t lineSize = line.size();
    for (std::size_t i = 0; i < lineSize; ++i)
    {
      if (std::isspace(std::string_view::traits_type::to_int_type(line[i])))
      {
        if (i > 0)
        {
          output.emplace_back(line.substr(0,i));
        }
        line = line.substr(i+1);
        lineSize -= i + 1;
        i = 0;
      }
    }
    if (line.size() > 0)
    {
      output.emplace_back(line);
    }
    return output;
  }
}

void FileSystem::AddDirectory(std::string_view name)
{
  if (!cwd) cwd = &root;

  if (!HasDirectory(name))
    cwd->subDirectories.emplace_back(Directory{std::string(name), cwd});
}

void FileSystem::AddFile(std::string_view name, std::size_t size)
{
  if (!cwd) cwd = &root;

  if (!HasFile(name))
    cwd->files.emplace_back(File{std::string(name), size});
}

bool FileSystem::HasDirectory(std::string_view name) const
{
  bool found = false;
  if (cwd)
  {
    for (auto& dir : cwd->subDirectories)
    {
      if (dir.name == name)
      {
        found = true;
        break;
      }
    }
  }
  return found;
}

bool FileSystem::HasFile(std::string_view name) const
{
  bool found = false;
  if (cwd)
  {
    for (auto& file : cwd->files)
    {
      if (file.name == name)
      {
        found = true;
        break;
      }
    }
  }
  return found;

}

void FileSystem::ChangeDirectory(std::string_view name)
{
  if (!cwd) cwd = &root;

  if (name == "..")
  {
    cwd = cwd->pParent;
  }
  else if (name == "/")
  {
    cwd = &root;
  }
  else
  {
    for (auto& dir : cwd->subDirectories)
    {
      if (dir.name == name)
      {
        cwd = &dir;
        break;
      }
    }
  }
}

std::size_t FileSystem::GetDirectorySize(Directory const* pDir) const
{
  if (!pDir) pDir = &root;

  std::size_t total = 0;
  for (auto& f : pDir->files)
  {
    total += f.size;
  }

  for (auto& d : pDir->subDirectories)
  {
    total += GetDirectorySize(&d);
  }
  return total;
}

std::vector<Directory const*> FileSystem::GetDirectories(Directory const* pStart) const
{
  if (!pStart) pStart = &root;

  std::vector<Directory const*> dirs{pStart};

  // Iterate through breadth first
  for (std::size_t i = 0; i < dirs.size(); ++i)
  {
    for (auto& d : dirs[i]->subDirectories)
    {
      dirs.push_back(&d);
    }
  }
  return dirs;
}

std::vector<File const*> FileSystem::GetFiles(Directory const* pStart) const
{
  std::vector<File const*> files;
  auto dirs = GetDirectories(pStart);
  for (auto pDir : dirs)
  {
    for (auto& file : pDir->files)
    {
      files.push_back(&file);
    }
  }
  return files;
}

void CommandParser::ParseLine(std::string_view line)
{
  if (line[0] == '$')
  {
    currentCommand = Commands::NONE;
    ParseLine(line.substr(1));
  }

  // If no command, then we need to read a new command
  switch (currentCommand)
  {
    default:
    case Commands::NONE:
    {
      auto words = Util::Split(line);
      if (!words.empty())
      {
        if (words[0] == "cd")
        {
          currentCommand = Commands::CD;
          if (words.size() > 1)
          {
            fileSystem.ChangeDirectory(words[1]);
          }
        }
        else if (words[0] == "ls") currentCommand = Commands::LS;
      }
      break;
    }
    case Commands::LS:
    {
      auto words = Util::Split(line);
      if (words.size() > 1)
      {
        if (words[0] == "dir")
        {
          fileSystem.AddDirectory(words[1]);
        }
        else
        {
          // Visual studio gave a weird error about length zero arrays when I tried to use words[0] here
          std::stringstream parseStream(std::string(words.front()));
          std::size_t size = 0;
          parseStream >> size;
          fileSystem.AddFile(words[1], size);
        }
      }
    }
  }
}
  
std::size_t CommandParser::GetDirectorySize(Directory const* pDir) const
{
  return fileSystem.GetDirectorySize(pDir);
}

std::vector<Directory const*> CommandParser::GetDirectories(Directory const* pStart) const
{
  return fileSystem.GetDirectories(pStart);
}

std::vector<File const*> CommandParser::GetFiles() const
{
  return fileSystem.GetFiles();
}