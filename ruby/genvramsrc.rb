# coding: utf-8
require 'bundler/setup'
require 'pycall/import'
include PyCall::Import

WIDTH = 384

pyfrom :PIL, import: [:Image, :ImageFont, :ImageDraw]

font = ImageFont.truetype(font: '/usr/share/fonts/opentype/noto/NotoSansCJK-Black.ttc', size: 14)
image = Image.new(:RGB, [WIDTH, 16])
draw = ImageDraw.Draw(image)
draw.text([0, -4], '【Wi-Fi display by Yagshi】待機中/Standing by...', font: font)
word1 = 0
word2 = 0
src1 = ""
src2 = ""
bit = 1 << 31
16.times {|y|
  src1 = src1 + "{"
  src2 = src2 + "{"
  WIDTH.times {|x|
    r, g, b = image.getpixel(PyCall::Tuple.([x, y]))
    i = 0.3 * r + 0.59 * g + 0.11 * b
    if i > 120 then
      word1 = word1 + bit
      word2 = word2 + bit if i > 180
    elsif i > 80 then
      word2 = word2 + bit
    end
    bit = bit >> 1
    if bit == 0 then
      src1 += "0x%08x, " % [word1]
      src2 += "0x%08x, " % [word2]
      bit = 1 << 31
      word1 = 0
      word2 = 0
    end
  }
  src1 = src1[0..-3]  # 最後の,を抜く
  src2 = src2[0..-3]
  src1 += "},\n"
  src2 += "},\n"
}
image.show()
src1 = src1[0..-3]  # 最後の,を抜く
src2 = src2[0..-3]
puts "{\n" + src1 + "},"
puts "{\n" + src2 + "},"

