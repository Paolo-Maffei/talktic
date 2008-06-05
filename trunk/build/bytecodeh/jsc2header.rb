#!/usr/bin/ruby

c = 0;
File.open(ARGV.shift) do |f|
  print "unsigned char EEMEM _bytecode[] = {\r\n"
  f.each_byte do |b|
    print "0x#{b.to_s(16)}"
    if ! f.eof?
      print ","
      if c % 8 == 7 then
        print "\r\n"
      end
    end
    c += 1
  end
  print "};\r\n"
  print "unsigned int _bytecode_size = #{c};\r\n"
end
