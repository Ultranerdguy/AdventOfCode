#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

typedef std::vector<std::string> TImage;

class CTile
{
  TImage m_image;
  std::vector<std::vector<int16_t>> m_transformIDs;

public:
  int64_t m_ID;
  enum class Transforms {I, R, RR, RRR, V, VR, VRR, VRRR};

  void SetID(const int64_t id)
  {
    m_ID = id;
  }

  template <typename Iterator>
  void AddRow(Iterator start, const Iterator end)
  {
    auto& lastRow = m_image.emplace_back();
    while (start != end)
    {
      lastRow.push_back(*start);
      ++start;
    }
  }
  
  void ProcessTransformIDs()
  {
    TImage localImage = m_image;
    // I
    m_transformIDs.push_back(GetImageIDs(localImage));
    // R
    localImage = Rotate(localImage);
    m_transformIDs.push_back(GetImageIDs(localImage));
    // RR
    localImage = Rotate(localImage);
    m_transformIDs.push_back(GetImageIDs(localImage));
    // RRR
    localImage = Rotate(localImage);
    m_transformIDs.push_back(GetImageIDs(localImage));
    // V
    localImage = Flip(m_image);
    m_transformIDs.push_back(GetImageIDs(localImage));
    // VR
    localImage = Rotate(localImage);
    m_transformIDs.push_back(GetImageIDs(localImage));
    // VRR
    localImage = Rotate(localImage);
    m_transformIDs.push_back(GetImageIDs(localImage));
    // VRRR
    localImage = Rotate(localImage);
    m_transformIDs.push_back(GetImageIDs(localImage));
  }

  static TImage TransformImage(const TImage& img, Transforms transform)
  {
    TImage out = img;
    switch (transform)
    {
      default:
        break;
      case Transforms::V:
      case Transforms::VR:
      case Transforms::VRR:
      case Transforms::VRRR:
        out = CTile::Flip(out);
        break;
    }

    switch (transform)
    {
      default:
        break;
      case Transforms::VRRR:
      case Transforms::RRR:
        out = CTile::Rotate(out); 
        [[Fallthrough]];
      case Transforms::VRR:
      case Transforms::RR:
        out = CTile::Rotate(out);
        [[Fallthrough]];
      case Transforms::VR:
      case Transforms::R:
        out = CTile::Rotate(out);
        break;
    }
    return out;
  }

  std::vector<int16_t>& GetTransformIDs(Transforms t)
  {
    return m_transformIDs[static_cast<int>(t)];
  }

  static std::vector<int16_t> GetImageIDs(const TImage& img)
  {
    std::vector<int16_t> ids(4, 0);
    const size_t rows = img.size();
    const size_t cols = img[0].size();

    int16_t nextValue = 0;
    for (size_t i = 0; i < cols; ++i)
    {
      nextValue <<= 1;
      nextValue += img[0][i] == '#' ? 1 : 0;
    }
    ids[0] = nextValue;
     nextValue = 0;
    for (size_t i = 0; i < rows; ++i)
    {
      nextValue <<= 1;
      nextValue += img[i][cols-1] == '#' ? 1 : 0;
    }
    ids[1] = nextValue;
     nextValue = 0;
    for (size_t i = 0; i < cols; ++i)
    {
      nextValue <<= 1;
      nextValue += img[rows-1][i] == '#' ? 1 : 0;
    }
    ids[2] = nextValue;
     nextValue = 0;
    for (size_t i = 0; i < cols; ++i)
    {
      nextValue <<= 1;
      nextValue += img[i][0] == '#' ? 1 : 0;
    }
    ids[3] = nextValue;
    return ids;
  }

  static TImage Rotate(const TImage& in)
  {
    const size_t rows = in.size();
    const size_t cols = in[0].size();
    TImage out(cols, TImage::value_type(rows, 0));

    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        out[i][j] = in[j][rows - i - 1];
      }
    }
    return out;
  }

  static TImage Flip(const TImage& in)
  {
    const size_t rows = in.size();
    const size_t cols = in[0].size();
    TImage out(cols, TImage::value_type(rows, 0));

    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        out[i][j] = in[j][i];
      }
    }
    return out;
  }

  int MatchesTransform(int16_t t, int16_t l, int16_t b, int16_t r) const
  {
    for (int i = 0; i < 8; ++i)
    {
      bool isValid = true;
      if ((t != -1 && t != m_transformIDs[i][0])
        || (l != -1 && l != m_transformIDs[i][3])
        || (b != -1 && b != m_transformIDs[i][2])
        || (r != -1 && r != m_transformIDs[i][1]))
        isValid = false;
      if (isValid)
        return i;
    }
    return -1;
  }

  const TImage& GetImage() const
  {
    return m_image;
  }
};

class CJigsaw
{
  std::vector<CTile> m_tiles;

public:
  void AddTile(CTile&& tile)
  {
    m_tiles.emplace_back(tile);
  }

  void ProcessTiles()
  {
    for (auto& tile : m_tiles)
    {
      tile.ProcessTransformIDs();
    }
  }

private:
  struct Tile
  {
    CTile* pTile = nullptr;
    CTile::Transforms transform = CTile::Transforms::I;
    int16_t t = (int16_t)-1;
    int16_t r = (int16_t)-1;
    int16_t b = (int16_t)-1;
    int16_t l = (int16_t)-1;
  };
  bool RecursiveTiling(std::map<int, std::map<int, Tile>>& _jigsaw, std::set<CTile*> availableTiles)
  {
    auto jigsaw = _jigsaw;
    while (!availableTiles.empty())
    {
      for (auto& [i, m] : jigsaw)
      {
        for (auto& [j, t] : m)
        {
          if (t.pTile != nullptr)
          {
            jigsaw[i][j + 1].b = t.pTile->GetTransformIDs(t.transform)[0];
            jigsaw[i + 1][j].l = t.pTile->GetTransformIDs(t.transform)[1];
            jigsaw[i][j - 1].t = t.pTile->GetTransformIDs(t.transform)[2];
            jigsaw[i - 1][j].r = t.pTile->GetTransformIDs(t.transform)[3];
          }
        }
      }

      for (auto& [i, m] : jigsaw)
      {
        for (auto& [j, t] : m)
        {
          if (t.pTile == nullptr)
          {
            if (!(t.r == t.l == t.t == t.b == (int16_t)-1))
            {
              for (auto tile = availableTiles.begin(); tile != availableTiles.end(); ++tile)
              {
                if (*tile)
                {
                  int match = (*tile)->MatchesTransform(t.t, t.l, t.b, t.r);
                  if (match != -1)
                  {
                    t.pTile = *tile;
                    t.transform = static_cast<CTile::Transforms>(match);
                    availableTiles.erase(tile);
                    if (RecursiveTiling(jigsaw, availableTiles))
                    {
                      _jigsaw = jigsaw;
                      return true;
                    }
                    else
                    {
                      tile = availableTiles.insert(t.pTile).first;
                      t.pTile = nullptr;
                    }
                  }
                }
              }
            }
          }
        }
      }
      return false;
    }
    _jigsaw = jigsaw;
    return true;
  }

public:
  std::map<int, std::map<int, Tile>> FindTiling()
  {
    std::set<CTile*> availableTiles;
    for (auto t = m_tiles.begin(); t != m_tiles.end(); ++t)
      availableTiles.insert(&*t);
    std::map<int, std::map<int, Tile>> jigsaw;

    jigsaw[0][0] = Tile{ &m_tiles[0] };
    availableTiles.erase(&m_tiles[0]);
    RecursiveTiling(jigsaw, availableTiles);
    return jigsaw;
  }

  static TImage CondenseTiling(const std::map<int, std::map<int, Tile>>& tiling)
  {
    TImage img;
    int minI = std::numeric_limits<int>::max();
    int minJ = std::numeric_limits<int>::max();
    for (auto& [i, m] : tiling)
    {
      for (auto& [j, t] : m)
      {
        if (t.pTile)
        {
          minI = std::min(minI, i);
          minJ = std::min(minJ, j);
          TImage tileImage = CTile::TransformImage(t.pTile->GetImage(), t.transform);
          for (size_t x = 1; x < tileImage.size()-1; ++x)
          {
            typedef signed long long sll;
            const size_t imgRow = ((sll)j - (sll)minJ) * (tileImage.size() - 2) + x-1;
            
            if (img.size() < imgRow + 1)
              img.resize(imgRow + 1);

            for (size_t y = 1; y < tileImage[x].size() - 1; ++y)
            {
              const size_t imgCol = ((sll)i - (sll)minI) * (tileImage[x].size() - 2) + y-1;

              if (img[imgRow].size() < imgCol + 1)
                img[imgRow].resize(imgCol + 1);

              img[imgRow][imgCol] = tileImage[tileImage.size() - x - 1][y];
            }
          }
        }
      }
    }
    return img;
  }

  static size_t CountWater(TImage img)
  {
    static const TImage seaMonster{
      "                  # ",
      "#    ##    ##    ###",
      " #  #  #  #  #  #   "};
    size_t hashCount = 0;

    bool hasMonster = false;
    for (size_t y = 0; y < img.size()-seaMonster.size(); ++y)
    {
      for (size_t x = 0; x < img[y].size()-seaMonster[0].size(); ++x)
      {
        // Check if the box with top left corner x,y is a monster
        bool valid = true;
        for (size_t j = 0; j < seaMonster.size(); ++j)
        {
          for (size_t i = 0; i < seaMonster[0].size(); ++i)
          {
            if (seaMonster[j][i] == '#' && img[y + j][x + i] == '.')
            {
              valid = false;
              break;
            }
          }
          if (!valid) break;
        }
        if (valid)
        {
          // Swap all # to O. No necessary, but makes it easier
          hasMonster = true;
          for (size_t j = 0; j < seaMonster.size(); ++j)
          {
            for (size_t i = 0; i < seaMonster[0].size(); ++i)
            {
              if (seaMonster[j][i] == '#')
              {
                img[y + j][x + i] = 'O';
              }
            }
          }
        }
      }
    }
    if (hasMonster)
    {
      // Count #
      for (size_t y = 0; y < img.size(); ++y)
      {
        for (size_t x = 0; x < img[y].size(); ++x)
        {
          if (img[y][x] == '#') ++hashCount;
        }
      }
    }
    return hashCount;
  }

  static size_t CountAllTransformMonsters(const TImage& img)
  {
    size_t hashCount = 0;
    hashCount += CountWater(CTile::TransformImage(img, CTile::Transforms::I));
    hashCount += CountWater(CTile::TransformImage(img, CTile::Transforms::R));
    hashCount += CountWater(CTile::TransformImage(img, CTile::Transforms::RR));
    hashCount += CountWater(CTile::TransformImage(img, CTile::Transforms::RRR));
    hashCount += CountWater(CTile::TransformImage(img, CTile::Transforms::V));
    hashCount += CountWater(CTile::TransformImage(img, CTile::Transforms::VR));
    hashCount += CountWater(CTile::TransformImage(img, CTile::Transforms::VRR));
    hashCount += CountWater(CTile::TransformImage(img, CTile::Transforms::VRRR));
    return hashCount;
  }
};

int main()
{
  std::ifstream file("Input.txt");

  CJigsaw pattern;

  while (file)
  {
    CTile tile;
    std::string line;
    std::getline(file, line);
    if (line.empty()) continue;
    line = line.substr(5,line.size()-6);
    tile.SetID(std::stoull(line));
    while (true)
    {
      line="";
      std::getline(file, line);
      if (line.empty()) break;
      tile.AddRow(line.begin(), line.end());
    }
    pattern.AddTile(std::move(tile));
  }

  pattern.ProcessTiles();
  
  // Part 1
  auto jigsaw = pattern.FindTiling();
  int lowXIndex = std::numeric_limits<int>::max();
  int highXIndex = std::numeric_limits<int>::min();
  int lowYIndex = std::numeric_limits<int>::max();
  int highYIndex = std::numeric_limits<int>::min();

  for (auto& [i, m] : jigsaw)
  {
    for (auto& [j, t] : m)
    {
      if (t.pTile)
      {
        lowXIndex = std::min(lowXIndex, i);
        lowYIndex = std::min(lowYIndex, j);
        highXIndex = std::max(highXIndex, i);
        highYIndex = std::max(highYIndex, j);
      }
    }
  }
  uint64_t prod = 1;
  for (auto [x, y] : std::initializer_list<std::pair<int, int>>
    { {lowXIndex, lowYIndex}
    , {lowXIndex, highYIndex}
    , {highXIndex, lowYIndex}
    , {highXIndex, highYIndex} })
  {
    prod *= jigsaw[x][y].pTile->m_ID;
  }
  std::cout << "Part 1: " << prod << '\n';

  // Part 2
  TImage condensed = CJigsaw::CondenseTiling(jigsaw);
  std::cout << "Part 2: " << CJigsaw::CountAllTransformMonsters(condensed) << '\n';
}