# LinuxStylize
Just a neat little C program I made that allows you to add color &amp; style to text in terminal.

# Compiling
`gcc linux_out.c -o stylize` This will just be an executable. If you want to do anything fancy with it, figure it out yourself.

# Using
You can pipe data in, so like `echo my data here | ./stylize -c Red -s Bold`. Right now, multi-line pipes aren't supported. So `cat myfile.txt | ./stylize -c Red -s Bold` won't work. You can also pass data through the command line `./stylize -c orange -s underline -i your message goes here`.

# Help
Just do `./stylize --help`
