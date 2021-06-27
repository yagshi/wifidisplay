# coding: utf-8
# Wi-Fi display に puts する
# usage: ledputs.rb string

require 'bundler/setup'
require 'pycall/import'
require 'net/http'
include PyCall::Import

WIDTH = 384

pyfrom :PIL, import: [:Image, :ImageFont, :ImageDraw]

font = ImageFont.truetype(font: '/usr/share/fonts/opentype/noto/NotoSansCJK-Black.ttc', size: 14)
image = Image.new(:RGB, [WIDTH, 16])
draw = ImageDraw.Draw(image)
draw.text([0, -4], ARGV[0], font: font)

word1 = 0
word2 = 0
bit = 1 << 31
16.times {|y|
  str1 = ""
  str2 = ""
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
      str1 += "%08x" % [word1]
      str2 += "%08x" % [word2]
      bit = 1 << 31
      word1 = 0
      word2 = 0
    end
  }
  Net::HTTP.get_response(URI.parse("http://wifidisplay.local/set?row=#{y}&plane=0&data=#{str1}"))
  Net::HTTP.get_response(URI.parse("http://wifidisplay.local/set?row=#{y}&plane=1&data=#{str2}"))
}

