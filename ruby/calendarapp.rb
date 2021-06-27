# coding: utf-8
# Wi-Fi display に puts する
# usage: ledputs.rb string

require 'bundler/setup'
require 'pycall/import'
require 'net/http'
require 'google/apis/calendar_v3'
include PyCall::Import

WIDTH = 384
KEYFILE = 'iotdisplay-405447f1d61a.json'.freeze
CALENDAR_ID = 'kqjf08tfsnanv8p5rl2pa4p9p0@group.calendar.google.com'.freeze

pyfrom :PIL, import: [:Image, :ImageFont, :ImageDraw]

font = ImageFont.truetype(font: '/usr/share/fonts/opentype/noto/NotoSansCJK-Black.ttc', size: 14)
image = Image.new(:RGB, [WIDTH, 16])
draw = ImageDraw.Draw(image)

# Google calendar setup
service = Google::Apis::CalendarV3::CalendarService.new
service.authorization = Google::Auth::ServiceAccountCredentials.make_creds(
  json_key_io: File.open(KEYFILE),
  scope: Google::Apis::CalendarV3::AUTH_CALENDAR_READONLY
)


def get_calendar(service)
  begin
    resp = service.list_events(
      CALENDAR_ID,
      max_results: 1,
      order_by:    :startTime,
      time_min:    DateTime.now.rfc3339,
      single_events: true,
    )
    ev = resp.items[0]
    dt = ev.start.date_time || ev.start.date
    now = DateTime.now
    str = ""
    if dt then
      if dt.year == now.year && dt.month == now.month && dt.day == now.day then
        if dt.class == DateTime then
          str += "%02d:%02d- " % [dt.hour, dt.min]
        else
          str += "本日: "
        end
      else
        str += "%02d日: " % [dt.day]
      end
    end
    str += ev.summary
  rescue => e
    p e
  end
  str
end

while true
  d = Time.now
  str = get_calendar(service) + "  "
  puts str
  draw.rectangle([0, 0, WIDTH, 16], fill: PyCall::Tuple.([0, 0, 0, 0]))
  text_width, _ = font.getsize(str)
  draw.text([0, -4], str * (WIDTH / text_width), font: font)
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
  begin
    Net::HTTP.get_response(URI.parse("http://wifidisplay.local/set?row=#{y}&plane=0&data=#{str1}"))
    Net::HTTP.get_response(URI.parse("http://wifidisplay.local/set?row=#{y}&plane=1&data=#{str2}"))
  rescue => e
    p e
  end
}
sleep(30)
end