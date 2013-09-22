
env = Environment(PIC = '24FJ128GB206', 
                  CC = 'xc16-gcc', 
                  PROGSUFFIX = '.elf', 
                  CFLAGS = '-g -omf=elf -x c -mcpu=$PIC', 
                  LINKFLAGS = '-omf=elf -mcpu=$PIC -Wl,--script="app_p24FJ128GB206.gld"', 
                  CPPPATH = '../lib')
env.PrependENVPath('PATH', '/opt/microchip/xc16/v1.11/bin')
bin2hex = Builder(action = 'xc16-bin2hex $SOURCE -omf=elf',
                  suffix = 'hex', 
                  src_suffix = 'elf')
env.Append(BUILDERS = {'Hex' : bin2hex})
list = Builder(action = 'xc16-objdump -S -D $SOURCE > $TARGET', 
               suffix = 'lst', 
               src_suffix = 'elf')
env.Append(BUILDERS = {'List' : list})

upload = Builder(action = '../site_scons/bootloadercmd.py -i servo.hex -w')
env.Append(BUILDERS = {'Upload' : upload})

env.Program('servo', ['servo.c',
                      '../lib/timer.c',
                      '../lib/ui.c',
                      '../lib/uart.c',
                      '../lib/usb.c',
                      'descriptors.c',
                      '../lib/pin.c',
                      '../lib/oc.c'])
env.Hex('servo')
env.List('servo')
env.Upload()
