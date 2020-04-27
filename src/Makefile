COMPILER_FLAGS=-Werror -I/opt/local/include/SDL2 -D_THREAD_SAFE -DVERSION=\"0.0.4\" -g -ggdb3 -O3 # AUTOGEN
    
CLANG_COMPILER_WARNINGS=-Wall -Wmissing-prototypes -std=c++1z -stdlib=libc++ # AUTOGEN
GCC_COMPILER_WARNINGS=-x c++ -Wall -std=c++2a -ffast-math  # AUTOGEN
COMPILER_WARNINGS=$(CLANG_COMPILER_WARNINGS) # AUTOGEN
COMPILER_WARNINGS=$(GCC_COMPILER_WARNINGS) # AUTOGEN
# CC=clang++ # AUTOGEN
CC=g++ # AUTOGEN
    
EXE= # AUTOGEN
DSYM=dsymutil ../sph_sdl # AUTOGEN
LDLIBS=-L/opt/local/lib -lSDL2 -lSDL2_mixer -lSDL2_ttf -funwind-tables -rdynamic -Wl,-framework,Opengl # AUTOGEN
CFLAGS=$(COMPILER_FLAGS) $(COMPILER_WARNINGS) # AUTOGEN

NAME=sph_sdl
OBJDIR=.o

GAME_OBJECTS=				\
    $(OBJDIR)/ascii.o 			\
    $(OBJDIR)/ascii_box.o 		\
    $(OBJDIR)/color.o			\
    $(OBJDIR)/dir.o			\
    $(OBJDIR)/command.o 		\
    $(OBJDIR)/console.o 		\
    $(OBJDIR)/file.o 			\
    $(OBJDIR)/file_read.o 		\
    $(OBJDIR)/font.o 			\
    $(OBJDIR)/game.o 			\
    $(OBJDIR)/game_config_keyboard.o	\
    $(OBJDIR)/game_display.o 		\
    $(OBJDIR)/game_error.o 		\
    $(OBJDIR)/game_fini.o 		\
    $(OBJDIR)/game_init.o 		\
    $(OBJDIR)/game_notice.o 		\
    $(OBJDIR)/game_quit.o 		\
    $(OBJDIR)/gfx.o			\
    $(OBJDIR)/gl.o 			\
    $(OBJDIR)/hexdump.o 		\
    $(OBJDIR)/log.o 			\
    $(OBJDIR)/main.o 			\
    $(OBJDIR)/minilzo.o 		\
    $(OBJDIR)/pcg_basic.o 		\
    $(OBJDIR)/ptrcheck.o 		\
    $(OBJDIR)/sdl.o 			\
    $(OBJDIR)/slre.o 			\
    $(OBJDIR)/sprintf.o 		\
    $(OBJDIR)/stb_image.o 		\
    $(OBJDIR)/string.o 			\
    $(OBJDIR)/tex.o 			\
    $(OBJDIR)/tile.o 			\
    $(OBJDIR)/time.o 			\
    $(OBJDIR)/token.o 			\
    $(OBJDIR)/traceback.o 		\
    $(OBJDIR)/ttf.o 			\
    $(OBJDIR)/util.o 			\
    $(OBJDIR)/wid.o 			\
    $(OBJDIR)/wid_console.o 		\
    $(OBJDIR)/wid_minicon.o 		\
    $(OBJDIR)/wid_popup.o 		\
    $(OBJDIR)/wid_test.o 		\
    $(OBJDIR)/wid_text_box.o 		\
    $(OBJDIR)/wid_tiles.o 		\

#
# compile
#
$(OBJDIR)/%.o: %.cpp
	@echo $(CC) $(EXTRA_CFLAGS) $(CFLAGS) -c -o $@ $<
	@$(CC) $(EXTRA_CFLAGS) $(CFLAGS) -c -o $@ $<

#
# link
#
TARGET_GAME=$(NAME)$(EXE)
$(TARGET_GAME): $(GAME_OBJECTS)
	$(CC) $(GAME_OBJECTS) $(LDLIBS) -o ../$(TARGET_GAME)

#
# To force clean and avoid "up to date" warning.
#
.PHONY: clean
.PHONY: clobber

clean:
	rm -rf ../$(TARGET_GAME) ../stdout.txt ../stderr.txt
	rm -rf $(GAME_OBJECTS) $(TARGET_GAME) stdout.txt stderr.txt

clobber: clean
	rm -rf $(OBJDIR)
	mkdir -p $(OBJDIR)

valgrind:
	valgrind --gen-suppressions=all --leak-check=full --suppressions=valgrind.suppress --error-limit=no ../$(NAME)

all: $(TARGET_GAME)
	$(DSYM)
# DO NOT DELETE

.o/ascii.o: my_ascii.h /usr/include/wchar.h /usr/include/_types.h
.o/ascii.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/ascii.o: /usr/include/sys/_symbol_aliasing.h
.o/ascii.o: /usr/include/sys/_posix_availability.h
.o/ascii.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/ascii.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ascii.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/ascii.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/ascii.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/machine/types.h
.o/ascii.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/ascii.o: /usr/include/sys/_types/_int16_t.h
.o/ascii.o: /usr/include/sys/_types/_int32_t.h
.o/ascii.o: /usr/include/sys/_types/_int64_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int8_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int16_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int32_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int64_t.h
.o/ascii.o: /usr/include/sys/_types/_intptr_t.h
.o/ascii.o: /usr/include/sys/_types/_uintptr_t.h
.o/ascii.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ascii.o: /usr/include/sys/_types/_rune_t.h
.o/ascii.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/ascii.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/ascii.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/ascii.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/ascii.o: /usr/include/secure/_common.h /usr/include/time.h
.o/ascii.o: /usr/include/sys/_types/_clock_t.h
.o/ascii.o: /usr/include/sys/_types/_time_t.h
.o/ascii.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ascii.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/ascii.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ascii.o: /usr/include/_ctype.h /usr/include/runetype.h my_point.h
.o/ascii.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/ascii.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/ascii.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/ascii.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/ascii.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/ascii.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/ascii.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/ascii.o: my_token.h my_string.h my_slre.h my_math.h /usr/include/math.h
.o/ascii.o: my_color.h my_font.h my_tile.h my_tex.h my_gl.h my_time.h
.o/ascii.o: /usr/include/assert.h /usr/include/unistd.h
.o/ascii.o: /usr/include/sys/unistd.h
.o/ascii.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ascii.o: /usr/include/sys/_types/_seek_set.h
.o/ascii.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/ascii.o: /usr/include/sys/_types/_pid_t.h
.o/ascii.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/ascii.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/ascii.o: /usr/include/sys/_types/_timeval.h
.o/ascii.o: /usr/include/sys/_types/_suseconds_t.h
.o/ascii.o: /usr/include/sys/_types/_sigset_t.h
.o/ascii.o: /usr/include/sys/_types/_fd_setsize.h
.o/ascii.o: /usr/include/sys/_types/_fd_set.h
.o/ascii.o: /usr/include/sys/_types/_fd_clr.h
.o/ascii.o: /usr/include/sys/_types/_fd_isset.h
.o/ascii.o: /usr/include/sys/_types/_fd_zero.h
.o/ascii.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ascii.o: /usr/include/sys/_types/_dev_t.h
.o/ascii.o: /usr/include/sys/_types/_mode_t.h
.o/ascii.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ascii.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/ascii_box.o: my_sdl.h my_command.h my_token.h my_string.h
.o/ascii_box.o: /usr/include/wchar.h /usr/include/_types.h
.o/ascii_box.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/ascii_box.o: /usr/include/sys/_symbol_aliasing.h
.o/ascii_box.o: /usr/include/sys/_posix_availability.h
.o/ascii_box.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/ascii_box.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ascii_box.o: /usr/include/Availability.h
.o/ascii_box.o: /usr/include/AvailabilityInternal.h
.o/ascii_box.o: /usr/include/sys/_types/_null.h
.o/ascii_box.o: /usr/include/sys/_types/_size_t.h
.o/ascii_box.o: /usr/include/sys/_types/_mbstate_t.h
.o/ascii_box.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ascii_box.o: /usr/include/sys/_types/_int8_t.h
.o/ascii_box.o: /usr/include/sys/_types/_int16_t.h
.o/ascii_box.o: /usr/include/sys/_types/_int32_t.h
.o/ascii_box.o: /usr/include/sys/_types/_int64_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int8_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int16_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int32_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int64_t.h
.o/ascii_box.o: /usr/include/sys/_types/_intptr_t.h
.o/ascii_box.o: /usr/include/sys/_types/_uintptr_t.h
.o/ascii_box.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ascii_box.o: /usr/include/sys/_types/_rune_t.h
.o/ascii_box.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/ascii_box.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/ascii_box.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/ascii_box.o: /usr/include/sys/_types/_ssize_t.h
.o/ascii_box.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ascii_box.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/ascii_box.o: /usr/include/sys/_types/_time_t.h
.o/ascii_box.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ascii_box.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/ascii_box.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ascii_box.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/ascii_box.o: my_font.h my_tile.h my_main.h my_pcg_basic.h
.o/ascii_box.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/ascii_box.o: /usr/include/_types/_uint8_t.h
.o/ascii_box.o: /usr/include/_types/_uint16_t.h
.o/ascii_box.o: /usr/include/_types/_uint32_t.h
.o/ascii_box.o: /usr/include/_types/_uint64_t.h
.o/ascii_box.o: /usr/include/_types/_intmax_t.h
.o/ascii_box.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/ascii_box.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/ascii_box.o: c_plus_plus_serializer.h my_ptrcheck.h my_tex.h my_gl.h
.o/ascii_box.o: my_color.h my_point.h my_math.h /usr/include/math.h
.o/ascii_box.o: my_ascii.h
.o/color.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/color.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/color.o: /usr/include/sys/_posix_availability.h
.o/color.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/color.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/color.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/color.o: /usr/include/sys/_pthread/_pthread_types.h
.o/color.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/color.o: /usr/include/sys/_types/_int8_t.h
.o/color.o: /usr/include/sys/_types/_int16_t.h
.o/color.o: /usr/include/sys/_types/_int32_t.h
.o/color.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/color.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/color.o: /usr/include/_types/_uint64_t.h
.o/color.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/color.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/color.o: /usr/include/sys/_types/_u_int16_t.h
.o/color.o: /usr/include/sys/_types/_u_int32_t.h
.o/color.o: /usr/include/sys/_types/_u_int64_t.h
.o/color.o: /usr/include/sys/_types/_uintptr_t.h
.o/color.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/color.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/color.o: /usr/include/sys/_types/_va_list.h
.o/color.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/color.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/color.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/color.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/color.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/color.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/color.o: /usr/include/sys/_types/_mbstate_t.h
.o/color.o: /usr/include/sys/_types/_ct_rune_t.h
.o/color.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/color.o: /usr/include/sys/_types/_clock_t.h
.o/color.o: /usr/include/sys/_types/_time_t.h
.o/color.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/color.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/color.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/color.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_gl.h
.o/color.o: my_color.h my_point.h my_math.h /usr/include/math.h
.o/command.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/command.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/command.o: /usr/include/sys/_posix_availability.h
.o/command.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/command.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/command.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/command.o: /usr/include/sys/_pthread/_pthread_types.h
.o/command.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/command.o: /usr/include/sys/_types/_int8_t.h
.o/command.o: /usr/include/sys/_types/_int16_t.h
.o/command.o: /usr/include/sys/_types/_int32_t.h
.o/command.o: /usr/include/sys/_types/_int64_t.h
.o/command.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/command.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/command.o: /usr/include/sys/_types/_intptr_t.h
.o/command.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/command.o: /usr/include/sys/_types/_u_int8_t.h
.o/command.o: /usr/include/sys/_types/_u_int16_t.h
.o/command.o: /usr/include/sys/_types/_u_int32_t.h
.o/command.o: /usr/include/sys/_types/_u_int64_t.h
.o/command.o: /usr/include/sys/_types/_uintptr_t.h
.o/command.o: /usr/include/_types/_intmax_t.h
.o/command.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/command.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/command.o: /usr/include/sys/_types/_va_list.h
.o/command.o: /usr/include/sys/_types/_size_t.h
.o/command.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/command.o: /usr/include/sys/_types/_off_t.h
.o/command.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/command.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/command.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/command.o: my_sdl.h my_command.h my_token.h my_string.h
.o/command.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/command.o: /usr/include/sys/_types/_ct_rune_t.h
.o/command.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/command.o: /usr/include/sys/_types/_clock_t.h
.o/command.o: /usr/include/sys/_types/_time_t.h
.o/command.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/command.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/command.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/command.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/command.o: my_wid.h my_wid_tiles.h my_tile.h my_tex.h my_gl.h my_color.h
.o/command.o: my_point.h my_math.h /usr/include/math.h my_size.h
.o/console.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/console.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/console.o: /usr/include/sys/_posix_availability.h
.o/console.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/console.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/console.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/console.o: /usr/include/sys/_pthread/_pthread_types.h
.o/console.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/console.o: /usr/include/sys/_types/_int8_t.h
.o/console.o: /usr/include/sys/_types/_int16_t.h
.o/console.o: /usr/include/sys/_types/_int32_t.h
.o/console.o: /usr/include/sys/_types/_int64_t.h
.o/console.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/console.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/console.o: /usr/include/sys/_types/_intptr_t.h
.o/console.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/console.o: /usr/include/sys/_types/_u_int8_t.h
.o/console.o: /usr/include/sys/_types/_u_int16_t.h
.o/console.o: /usr/include/sys/_types/_u_int32_t.h
.o/console.o: /usr/include/sys/_types/_u_int64_t.h
.o/console.o: /usr/include/sys/_types/_uintptr_t.h
.o/console.o: /usr/include/_types/_intmax_t.h
.o/console.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/console.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/console.o: /usr/include/sys/_types/_va_list.h
.o/console.o: /usr/include/sys/_types/_size_t.h
.o/console.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/console.o: /usr/include/sys/_types/_off_t.h
.o/console.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/console.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/console.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/console.o: my_sdl.h my_command.h my_token.h my_string.h
.o/console.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/console.o: /usr/include/sys/_types/_ct_rune_t.h
.o/console.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/console.o: /usr/include/sys/_types/_clock_t.h
.o/console.o: /usr/include/sys/_types/_time_t.h
.o/console.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/console.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/console.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/console.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/console.o: my_console.h my_color.h
.o/dir.o: /usr/include/sys/param.h /usr/include/sys/_types.h
.o/dir.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/dir.o: /usr/include/sys/_posix_availability.h
.o/dir.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dir.o: /usr/include/sys/_types/_null.h /usr/include/sys/types.h
.o/dir.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
.o/dir.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/dir.o: /usr/include/sys/_types/_int16_t.h
.o/dir.o: /usr/include/sys/_types/_int32_t.h
.o/dir.o: /usr/include/sys/_types/_int64_t.h
.o/dir.o: /usr/include/sys/_types/_u_int8_t.h
.o/dir.o: /usr/include/sys/_types/_u_int16_t.h
.o/dir.o: /usr/include/sys/_types/_u_int32_t.h
.o/dir.o: /usr/include/sys/_types/_u_int64_t.h
.o/dir.o: /usr/include/sys/_types/_intptr_t.h
.o/dir.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/machine/endian.h
.o/dir.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/dir.o: /usr/include/libkern/_OSByteOrder.h
.o/dir.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/dir.o: /usr/include/sys/_types/_u_char.h
.o/dir.o: /usr/include/sys/_types/_u_short.h /usr/include/sys/_types/_u_int.h
.o/dir.o: /usr/include/sys/_types/_caddr_t.h /usr/include/sys/_types/_dev_t.h
.o/dir.o: /usr/include/sys/_types/_blkcnt_t.h
.o/dir.o: /usr/include/sys/_types/_blksize_t.h
.o/dir.o: /usr/include/sys/_types/_gid_t.h
.o/dir.o: /usr/include/sys/_types/_in_addr_t.h
.o/dir.o: /usr/include/sys/_types/_in_port_t.h
.o/dir.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
.o/dir.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
.o/dir.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
.o/dir.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_off_t.h
.o/dir.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_clock_t.h
.o/dir.o: /usr/include/sys/_types/_size_t.h
.o/dir.o: /usr/include/sys/_types/_ssize_t.h
.o/dir.o: /usr/include/sys/_types/_time_t.h
.o/dir.o: /usr/include/sys/_types/_useconds_t.h
.o/dir.o: /usr/include/sys/_types/_suseconds_t.h
.o/dir.o: /usr/include/sys/_types/_rsize_t.h
.o/dir.o: /usr/include/sys/_types/_errno_t.h
.o/dir.o: /usr/include/sys/_types/_fd_def.h
.o/dir.o: /usr/include/sys/_types/_fd_setsize.h
.o/dir.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/dir.o: /usr/include/sys/_types/_fd_zero.h
.o/dir.o: /usr/include/sys/_types/_fd_isset.h
.o/dir.o: /usr/include/sys/_types/_fd_copy.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_cond_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_once_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_key_t.h
.o/dir.o: /usr/include/sys/_types/_fsblkcnt_t.h
.o/dir.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/syslimits.h
.o/dir.o: /usr/include/machine/param.h /usr/include/i386/param.h
.o/dir.o: /usr/include/i386/_param.h /usr/include/limits.h
.o/dir.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
.o/dir.o: /usr/include/i386/_limits.h /usr/include/sys/signal.h
.o/dir.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/dir.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/dir.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/dir.o: /usr/include/mach/machine/_structs.h
.o/dir.o: /usr/include/mach/i386/_structs.h
.o/dir.o: /usr/include/sys/_types/_sigaltstack.h
.o/dir.o: /usr/include/sys/_types/_ucontext.h
.o/dir.o: /usr/include/sys/_types/_sigset_t.h /usr/include/unistd.h
.o/dir.o: /usr/include/_types.h /usr/include/sys/unistd.h
.o/dir.o: /usr/include/sys/_types/_posix_vdisable.h
.o/dir.o: /usr/include/sys/_types/_seek_set.h /usr/include/_types/_uint64_t.h
.o/dir.o: /usr/include/_types/_uint32_t.h /usr/include/sys/select.h
.o/dir.o: /usr/include/sys/_types/_timespec.h
.o/dir.o: /usr/include/sys/_types/_timeval.h /usr/include/sys/_select.h
.o/dir.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/dir.o: /usr/include/sys/stat.h /usr/include/sys/_types/_s_ifmt.h
.o/dir.o: /usr/include/sys/_types/_filesec_t.h /usr/include/string.h
.o/dir.o: /usr/include/strings.h /usr/include/secure/_strings.h
.o/dir.o: /usr/include/secure/_common.h /usr/include/secure/_string.h
.o/dir.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/dir.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/dir.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/dir.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/dir.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/dir.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/dir.o: /usr/include/secure/_stdio.h my_array_bounds_check.h
.o/dir.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/dir.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/dir.o: /usr/include/sys/_types/_mbstate_t.h
.o/dir.o: /usr/include/sys/_types/_ct_rune_t.h
.o/dir.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/dir.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/dir.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/dir.o: /usr/include/ctype.h /usr/include/_ctype.h /usr/include/runetype.h
.o/dir.o: my_slre.h my_dir.h
.o/file.o: /usr/include/sys/stat.h /usr/include/sys/_types.h
.o/file.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/file.o: /usr/include/sys/_posix_availability.h
.o/file.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/file.o: /usr/include/sys/_pthread/_pthread_types.h
.o/file.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/file.o: /usr/include/sys/_types/_timespec.h /usr/include/machine/types.h
.o/file.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/file.o: /usr/include/sys/_types/_int16_t.h
.o/file.o: /usr/include/sys/_types/_int32_t.h
.o/file.o: /usr/include/sys/_types/_int64_t.h
.o/file.o: /usr/include/sys/_types/_u_int8_t.h
.o/file.o: /usr/include/sys/_types/_u_int16_t.h
.o/file.o: /usr/include/sys/_types/_u_int32_t.h
.o/file.o: /usr/include/sys/_types/_u_int64_t.h
.o/file.o: /usr/include/sys/_types/_intptr_t.h
.o/file.o: /usr/include/sys/_types/_uintptr_t.h
.o/file.o: /usr/include/sys/_types/_blkcnt_t.h
.o/file.o: /usr/include/sys/_types/_blksize_t.h
.o/file.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_ino_t.h
.o/file.o: /usr/include/sys/_types/_ino64_t.h
.o/file.o: /usr/include/sys/_types/_mode_t.h
.o/file.o: /usr/include/sys/_types/_nlink_t.h
.o/file.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/file.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_time_t.h
.o/file.o: /usr/include/sys/_types/_s_ifmt.h
.o/file.o: /usr/include/sys/_types/_filesec_t.h /usr/include/unistd.h
.o/file.o: /usr/include/_types.h /usr/include/sys/unistd.h
.o/file.o: /usr/include/sys/_types/_posix_vdisable.h
.o/file.o: /usr/include/sys/_types/_seek_set.h
.o/file.o: /usr/include/sys/_types/_size_t.h /usr/include/_types/_uint64_t.h
.o/file.o: /usr/include/_types/_uint32_t.h /usr/include/sys/_types/_ssize_t.h
.o/file.o: /usr/include/sys/_types/_pid_t.h
.o/file.o: /usr/include/sys/_types/_useconds_t.h
.o/file.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/file.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/file.o: /usr/include/sys/_types/_timeval.h
.o/file.o: /usr/include/sys/_types/_suseconds_t.h
.o/file.o: /usr/include/sys/_types/_sigset_t.h
.o/file.o: /usr/include/sys/_types/_fd_setsize.h
.o/file.o: /usr/include/sys/_types/_fd_set.h
.o/file.o: /usr/include/sys/_types/_fd_clr.h
.o/file.o: /usr/include/sys/_types/_fd_isset.h
.o/file.o: /usr/include/sys/_types/_fd_zero.h
.o/file.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/file.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/file.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/file.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/file.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/file.o: /usr/include/secure/_string.h /usr/include/time.h
.o/file.o: /usr/include/sys/_types/_clock_t.h my_main.h my_pcg_basic.h
.o/file.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/file.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/file.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_intmax_t.h
.o/file.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/file.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/file.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/file.o: /usr/include/secure/_stdio.h my_array_bounds_check.h
.o/file.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/file.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/file.o: /usr/include/sys/_types/_mbstate_t.h
.o/file.o: /usr/include/sys/_types/_ct_rune_t.h
.o/file.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/file.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/file.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/file.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_file.h
.o/file_read.o: /usr/include/string.h /usr/include/_types.h
.o/file_read.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/file_read.o: /usr/include/sys/_symbol_aliasing.h
.o/file_read.o: /usr/include/sys/_posix_availability.h
.o/file_read.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/file_read.o: /usr/include/sys/_pthread/_pthread_types.h
.o/file_read.o: /usr/include/Availability.h
.o/file_read.o: /usr/include/AvailabilityInternal.h
.o/file_read.o: /usr/include/sys/_types/_size_t.h
.o/file_read.o: /usr/include/sys/_types/_null.h
.o/file_read.o: /usr/include/sys/_types/_rsize_t.h
.o/file_read.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/file_read.o: /usr/include/sys/_types/_int8_t.h
.o/file_read.o: /usr/include/sys/_types/_int16_t.h
.o/file_read.o: /usr/include/sys/_types/_int32_t.h
.o/file_read.o: /usr/include/sys/_types/_int64_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int8_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int16_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int32_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int64_t.h
.o/file_read.o: /usr/include/sys/_types/_intptr_t.h
.o/file_read.o: /usr/include/sys/_types/_uintptr_t.h
.o/file_read.o: /usr/include/sys/_types/_errno_t.h
.o/file_read.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/file_read.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/file_read.o: /usr/include/secure/_string.h my_main.h my_pcg_basic.h
.o/file_read.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/file_read.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/file_read.o: /usr/include/_types/_uint16_t.h
.o/file_read.o: /usr/include/_types/_uint32_t.h
.o/file_read.o: /usr/include/_types/_uint64_t.h
.o/file_read.o: /usr/include/_types/_intmax_t.h
.o/file_read.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/file_read.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/file_read.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/file_read.o: /usr/include/sys/_types/_off_t.h /usr/include/secure/_stdio.h
.o/file_read.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/file_read.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/file_read.o: my_token.h my_string.h /usr/include/wchar.h
.o/file_read.o: /usr/include/sys/_types/_mbstate_t.h
.o/file_read.o: /usr/include/sys/_types/_ct_rune_t.h
.o/file_read.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/file_read.o: /usr/include/sys/_types/_clock_t.h
.o/file_read.o: /usr/include/sys/_types/_time_t.h
.o/file_read.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/file_read.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/file_read.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/file_read.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/file_read.o: my_ramdisk.h my_file.h
.o/font.o: my_ttf.h my_font.h my_tile.h my_main.h my_pcg_basic.h
.o/font.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/font.o: /usr/include/sys/_symbol_aliasing.h
.o/font.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/font.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/font.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/font.o: /usr/include/i386/_types.h
.o/font.o: /usr/include/sys/_pthread/_pthread_types.h
.o/font.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/font.o: /usr/include/sys/_types/_int8_t.h
.o/font.o: /usr/include/sys/_types/_int16_t.h
.o/font.o: /usr/include/sys/_types/_int32_t.h
.o/font.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/font.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/font.o: /usr/include/_types/_uint64_t.h
.o/font.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/font.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/font.o: /usr/include/sys/_types/_u_int16_t.h
.o/font.o: /usr/include/sys/_types/_u_int32_t.h
.o/font.o: /usr/include/sys/_types/_u_int64_t.h
.o/font.o: /usr/include/sys/_types/_uintptr_t.h
.o/font.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/font.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/font.o: /usr/include/sys/_types/_va_list.h
.o/font.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/font.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/font.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/font.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/font.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/font.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/font.o: /usr/include/sys/_types/_mbstate_t.h
.o/font.o: /usr/include/sys/_types/_ct_rune_t.h
.o/font.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/font.o: /usr/include/sys/_types/_clock_t.h
.o/font.o: /usr/include/sys/_types/_time_t.h
.o/font.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/font.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/font.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/font.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_tex.h
.o/font.o: my_gl.h my_color.h my_point.h my_math.h /usr/include/math.h
.o/game.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/game.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game.o: /usr/include/i386/_types.h
.o/game.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game.o: /usr/include/sys/_types/_int8_t.h
.o/game.o: /usr/include/sys/_types/_int16_t.h
.o/game.o: /usr/include/sys/_types/_int32_t.h
.o/game.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/game.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/game.o: /usr/include/_types/_uint64_t.h
.o/game.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/game.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/game.o: /usr/include/sys/_types/_u_int16_t.h
.o/game.o: /usr/include/sys/_types/_u_int32_t.h
.o/game.o: /usr/include/sys/_types/_u_int64_t.h
.o/game.o: /usr/include/sys/_types/_uintptr_t.h
.o/game.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/game.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/game.o: /usr/include/sys/_types/_va_list.h
.o/game.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/game.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/game.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/game.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/game.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/game.o: /usr/include/sys/_types/_mbstate_t.h
.o/game.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game.o: /usr/include/sys/_types/_clock_t.h
.o/game.o: /usr/include/sys/_types/_time_t.h
.o/game.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_config_keyboard.o: my_wid_minicon.h my_main.h my_pcg_basic.h
.o/game_config_keyboard.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/game_config_keyboard.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config_keyboard.o: /usr/include/sys/_posix_availability.h
.o/game_config_keyboard.o: /usr/include/Availability.h
.o/game_config_keyboard.o: /usr/include/AvailabilityInternal.h
.o/game_config_keyboard.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/game_config_keyboard.o: /usr/include/machine/_types.h
.o/game_config_keyboard.o: /usr/include/i386/_types.h
.o/game_config_keyboard.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_wchar_t.h
.o/game_config_keyboard.o: /usr/include/stdint.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_int8_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_int16_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_int32_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_int64_t.h
.o/game_config_keyboard.o: /usr/include/_types/_uint8_t.h
.o/game_config_keyboard.o: /usr/include/_types/_uint16_t.h
.o/game_config_keyboard.o: /usr/include/_types/_uint32_t.h
.o/game_config_keyboard.o: /usr/include/_types/_uint64_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_intptr_t.h
.o/game_config_keyboard.o: /usr/include/machine/types.h
.o/game_config_keyboard.o: /usr/include/i386/types.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_config_keyboard.o: /usr/include/_types/_intmax_t.h
.o/game_config_keyboard.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/game_config_keyboard.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_va_list.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_size_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_null.h
.o/game_config_keyboard.o: /usr/include/sys/stdio.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_off_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config_keyboard.o: /usr/include/secure/_stdio.h
.o/game_config_keyboard.o: /usr/include/secure/_common.h
.o/game_config_keyboard.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/game_config_keyboard.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h
.o/game_config_keyboard.o: my_command.h my_token.h my_string.h
.o/game_config_keyboard.o: /usr/include/wchar.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_rune_t.h
.o/game_config_keyboard.o: /usr/include/time.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_clock_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_time_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_timespec.h
.o/game_config_keyboard.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_wint_t.h
.o/game_config_keyboard.o: /usr/include/_types/_wctype_t.h
.o/game_config_keyboard.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/game_config_keyboard.o: /usr/include/runetype.h my_slre.h my_wid.h
.o/game_config_keyboard.o: my_wid_tiles.h my_tile.h my_tex.h my_gl.h
.o/game_config_keyboard.o: my_color.h my_point.h my_math.h
.o/game_config_keyboard.o: /usr/include/math.h my_size.h my_wid_console.h
.o/game_config_keyboard.o: my_wid_popup.h my_wid_text_box.h my_ascii.h
.o/game_config_keyboard.o: my_game_notice.h
.o/game_display.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_display.o: /usr/include/sys/cdefs.h
.o/game_display.o: /usr/include/sys/_symbol_aliasing.h
.o/game_display.o: /usr/include/sys/_posix_availability.h
.o/game_display.o: /usr/include/Availability.h
.o/game_display.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game_display.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_display.o: /usr/include/i386/_types.h
.o/game_display.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_display.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_display.o: /usr/include/sys/_types/_int8_t.h
.o/game_display.o: /usr/include/sys/_types/_int16_t.h
.o/game_display.o: /usr/include/sys/_types/_int32_t.h
.o/game_display.o: /usr/include/sys/_types/_int64_t.h
.o/game_display.o: /usr/include/_types/_uint8_t.h
.o/game_display.o: /usr/include/_types/_uint16_t.h
.o/game_display.o: /usr/include/_types/_uint32_t.h
.o/game_display.o: /usr/include/_types/_uint64_t.h
.o/game_display.o: /usr/include/sys/_types/_intptr_t.h
.o/game_display.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_display.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_display.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_display.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_display.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_display.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_display.o: /usr/include/_types/_intmax_t.h
.o/game_display.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/game_display.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_display.o: /usr/include/sys/_types/_va_list.h
.o/game_display.o: /usr/include/sys/_types/_size_t.h
.o/game_display.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_display.o: /usr/include/sys/_types/_off_t.h
.o/game_display.o: /usr/include/sys/_types/_ssize_t.h
.o/game_display.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_display.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/game_display.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h
.o/game_display.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/game_display.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_display.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_display.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_display.o: /usr/include/sys/_types/_clock_t.h
.o/game_display.o: /usr/include/sys/_types/_time_t.h
.o/game_display.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_display.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_display.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_display.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_error.o: minilzo.h /usr/include/limits.h /usr/include/sys/cdefs.h
.o/game_error.o: /usr/include/sys/_symbol_aliasing.h
.o/game_error.o: /usr/include/sys/_posix_availability.h
.o/game_error.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
.o/game_error.o: /usr/include/i386/_limits.h /usr/include/sys/syslimits.h
.o/game_error.o: /usr/include/stddef.h /usr/include/_types.h
.o/game_error.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_error.o: /usr/include/i386/_types.h
.o/game_error.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_error.o: /usr/include/sys/_types/_null.h
.o/game_error.o: /usr/include/sys/_types/_offsetof.h
.o/game_error.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/game_error.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_error.o: /usr/include/sys/_types/_int8_t.h
.o/game_error.o: /usr/include/sys/_types/_int16_t.h
.o/game_error.o: /usr/include/sys/_types/_int32_t.h
.o/game_error.o: /usr/include/sys/_types/_int64_t.h
.o/game_error.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_error.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_error.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_error.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_error.o: /usr/include/sys/_types/_intptr_t.h
.o/game_error.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_error.o: /usr/include/sys/_types/_rsize_t.h
.o/game_error.o: /usr/include/sys/_types/_size_t.h
.o/game_error.o: /usr/include/sys/_types/_wchar_t.h
.o/game_error.o: /usr/include/sys/_types/_wint_t.h lzodefs.h lzoconf.h
.o/game_error.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_error.o: /usr/include/Availability.h
.o/game_error.o: /usr/include/AvailabilityInternal.h /usr/include/stdint.h
.o/game_error.o: /usr/include/_types/_uint8_t.h
.o/game_error.o: /usr/include/_types/_uint16_t.h
.o/game_error.o: /usr/include/_types/_uint32_t.h
.o/game_error.o: /usr/include/_types/_uint64_t.h
.o/game_error.o: /usr/include/_types/_intmax_t.h
.o/game_error.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/game_error.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_error.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/game_error.o: /usr/include/sys/_types/_off_t.h
.o/game_error.o: /usr/include/sys/_types/_ssize_t.h
.o/game_error.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_error.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/game_error.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/game_error.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_error.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_error.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_error.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_error.o: /usr/include/sys/_types/_clock_t.h
.o/game_error.o: /usr/include/sys/_types/_time_t.h
.o/game_error.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_error.o: /usr/include/__wctype.h /usr/include/_types/_wctype_t.h
.o/game_error.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/game_error.o: /usr/include/runetype.h my_slre.h my_ascii.h my_point.h
.o/game_error.o: my_math.h /usr/include/math.h my_color.h my_wid_minicon.h
.o/game_error.o: my_wid.h my_wid_tiles.h my_tile.h my_tex.h my_gl.h my_size.h
.o/game_error.o: my_wid_console.h my_wid_popup.h my_wid_text_box.h
.o/game_error.o: my_game_error.h my_traceback.h
.o/game_fini.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_fini.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_fini.o: /usr/include/sys/_posix_availability.h
.o/game_fini.o: /usr/include/Availability.h
.o/game_fini.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game_fini.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_fini.o: /usr/include/i386/_types.h
.o/game_fini.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_fini.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_fini.o: /usr/include/sys/_types/_int8_t.h
.o/game_fini.o: /usr/include/sys/_types/_int16_t.h
.o/game_fini.o: /usr/include/sys/_types/_int32_t.h
.o/game_fini.o: /usr/include/sys/_types/_int64_t.h
.o/game_fini.o: /usr/include/_types/_uint8_t.h
.o/game_fini.o: /usr/include/_types/_uint16_t.h
.o/game_fini.o: /usr/include/_types/_uint32_t.h
.o/game_fini.o: /usr/include/_types/_uint64_t.h
.o/game_fini.o: /usr/include/sys/_types/_intptr_t.h
.o/game_fini.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_fini.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_fini.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_fini.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_fini.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_fini.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_fini.o: /usr/include/_types/_intmax_t.h
.o/game_fini.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/game_fini.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_fini.o: /usr/include/sys/_types/_va_list.h
.o/game_fini.o: /usr/include/sys/_types/_size_t.h
.o/game_fini.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_fini.o: /usr/include/sys/_types/_off_t.h
.o/game_fini.o: /usr/include/sys/_types/_ssize_t.h
.o/game_fini.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_fini.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/game_fini.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/game_fini.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_fini.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_fini.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_fini.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_fini.o: /usr/include/sys/_types/_clock_t.h
.o/game_fini.o: /usr/include/sys/_types/_time_t.h
.o/game_fini.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_fini.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_fini.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_fini.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_init.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_init.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_init.o: /usr/include/sys/_posix_availability.h
.o/game_init.o: /usr/include/Availability.h
.o/game_init.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game_init.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_init.o: /usr/include/i386/_types.h
.o/game_init.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_init.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_init.o: /usr/include/sys/_types/_int8_t.h
.o/game_init.o: /usr/include/sys/_types/_int16_t.h
.o/game_init.o: /usr/include/sys/_types/_int32_t.h
.o/game_init.o: /usr/include/sys/_types/_int64_t.h
.o/game_init.o: /usr/include/_types/_uint8_t.h
.o/game_init.o: /usr/include/_types/_uint16_t.h
.o/game_init.o: /usr/include/_types/_uint32_t.h
.o/game_init.o: /usr/include/_types/_uint64_t.h
.o/game_init.o: /usr/include/sys/_types/_intptr_t.h
.o/game_init.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_init.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_init.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_init.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_init.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_init.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_init.o: /usr/include/_types/_intmax_t.h
.o/game_init.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/game_init.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_init.o: /usr/include/sys/_types/_va_list.h
.o/game_init.o: /usr/include/sys/_types/_size_t.h
.o/game_init.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_init.o: /usr/include/sys/_types/_off_t.h
.o/game_init.o: /usr/include/sys/_types/_ssize_t.h
.o/game_init.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_init.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/game_init.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/game_init.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_init.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_init.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_init.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_init.o: /usr/include/sys/_types/_clock_t.h
.o/game_init.o: /usr/include/sys/_types/_time_t.h
.o/game_init.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_init.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_init.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_init.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_notice.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_notice.o: /usr/include/sys/cdefs.h
.o/game_notice.o: /usr/include/sys/_symbol_aliasing.h
.o/game_notice.o: /usr/include/sys/_posix_availability.h
.o/game_notice.o: /usr/include/Availability.h
.o/game_notice.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game_notice.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_notice.o: /usr/include/i386/_types.h
.o/game_notice.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_notice.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_notice.o: /usr/include/sys/_types/_int8_t.h
.o/game_notice.o: /usr/include/sys/_types/_int16_t.h
.o/game_notice.o: /usr/include/sys/_types/_int32_t.h
.o/game_notice.o: /usr/include/sys/_types/_int64_t.h
.o/game_notice.o: /usr/include/_types/_uint8_t.h
.o/game_notice.o: /usr/include/_types/_uint16_t.h
.o/game_notice.o: /usr/include/_types/_uint32_t.h
.o/game_notice.o: /usr/include/_types/_uint64_t.h
.o/game_notice.o: /usr/include/sys/_types/_intptr_t.h
.o/game_notice.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_notice.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_notice.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_notice.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_notice.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_notice.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_notice.o: /usr/include/_types/_intmax_t.h
.o/game_notice.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/game_notice.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_notice.o: /usr/include/sys/_types/_va_list.h
.o/game_notice.o: /usr/include/sys/_types/_size_t.h
.o/game_notice.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_notice.o: /usr/include/sys/_types/_off_t.h
.o/game_notice.o: /usr/include/sys/_types/_ssize_t.h
.o/game_notice.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_notice.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/game_notice.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h
.o/game_notice.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/game_notice.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_notice.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_notice.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_notice.o: /usr/include/sys/_types/_clock_t.h
.o/game_notice.o: /usr/include/sys/_types/_time_t.h
.o/game_notice.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_notice.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_notice.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_notice.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_notice.o: my_wid_minicon.h my_wid.h my_wid_tiles.h my_tile.h my_tex.h
.o/game_notice.o: my_gl.h my_color.h my_point.h my_math.h /usr/include/math.h
.o/game_notice.o: my_size.h my_wid_console.h my_wid_popup.h my_wid_text_box.h
.o/game_notice.o: my_ascii.h
.o/game_quit.o: my_wid_minicon.h my_main.h my_pcg_basic.h
.o/game_quit.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/game_quit.o: /usr/include/sys/_symbol_aliasing.h
.o/game_quit.o: /usr/include/sys/_posix_availability.h
.o/game_quit.o: /usr/include/Availability.h
.o/game_quit.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game_quit.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_quit.o: /usr/include/i386/_types.h
.o/game_quit.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_quit.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_quit.o: /usr/include/sys/_types/_int8_t.h
.o/game_quit.o: /usr/include/sys/_types/_int16_t.h
.o/game_quit.o: /usr/include/sys/_types/_int32_t.h
.o/game_quit.o: /usr/include/sys/_types/_int64_t.h
.o/game_quit.o: /usr/include/_types/_uint8_t.h
.o/game_quit.o: /usr/include/_types/_uint16_t.h
.o/game_quit.o: /usr/include/_types/_uint32_t.h
.o/game_quit.o: /usr/include/_types/_uint64_t.h
.o/game_quit.o: /usr/include/sys/_types/_intptr_t.h
.o/game_quit.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_quit.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_quit.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_quit.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_quit.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_quit.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_quit.o: /usr/include/_types/_intmax_t.h
.o/game_quit.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/game_quit.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_quit.o: /usr/include/sys/_types/_va_list.h
.o/game_quit.o: /usr/include/sys/_types/_size_t.h
.o/game_quit.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_quit.o: /usr/include/sys/_types/_off_t.h
.o/game_quit.o: /usr/include/sys/_types/_ssize_t.h
.o/game_quit.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_quit.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/game_quit.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/game_quit.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_quit.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_quit.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_quit.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_quit.o: /usr/include/sys/_types/_clock_t.h
.o/game_quit.o: /usr/include/sys/_types/_time_t.h
.o/game_quit.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_quit.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_quit.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_quit.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_quit.o: my_wid.h my_wid_tiles.h my_tile.h my_tex.h my_gl.h my_color.h
.o/game_quit.o: my_point.h my_math.h /usr/include/math.h my_size.h
.o/game_quit.o: my_wid_console.h my_wid_popup.h my_wid_text_box.h my_ascii.h
.o/gfx.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/gfx.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/gfx.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx.o: /usr/include/i386/_types.h
.o/gfx.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx.o: /usr/include/sys/_types/_int8_t.h
.o/gfx.o: /usr/include/sys/_types/_int16_t.h
.o/gfx.o: /usr/include/sys/_types/_int32_t.h
.o/gfx.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/gfx.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/gfx.o: /usr/include/sys/_types/_u_int8_t.h
.o/gfx.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/gfx.o: /usr/include/sys/_types/_va_list.h
.o/gfx.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/gfx.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/gfx.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/gfx.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/gfx.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/gfx.o: /usr/include/sys/_types/_clock_t.h
.o/gfx.o: /usr/include/sys/_types/_time_t.h
.o/gfx.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_tile.h
.o/gfx.o: my_tex.h my_gl.h my_color.h my_point.h my_math.h
.o/gfx.o: /usr/include/math.h my_gfx.h
.o/gl.o: my_gl.h my_color.h c_plus_plus_serializer.h my_point.h my_main.h
.o/gl.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gl.o: /usr/include/sys/_symbol_aliasing.h
.o/gl.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gl.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gl.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gl.o: /usr/include/i386/_types.h
.o/gl.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gl.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gl.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
.o/gl.o: /usr/include/sys/_types/_int32_t.h
.o/gl.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gl.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gl.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/gl.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/gl.o: /usr/include/sys/_types/_u_int8_t.h
.o/gl.o: /usr/include/sys/_types/_u_int16_t.h
.o/gl.o: /usr/include/sys/_types/_u_int32_t.h
.o/gl.o: /usr/include/sys/_types/_u_int64_t.h
.o/gl.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
.o/gl.o: /usr/include/_types/_uintmax_t.h my_callstack.h /usr/include/stdio.h
.o/gl.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gl.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/gl.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gl.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/gl.o: my_vector_bounds_check.h my_ptrcheck.h my_sdl.h my_command.h
.o/gl.o: my_token.h my_string.h /usr/include/wchar.h
.o/gl.o: /usr/include/sys/_types/_mbstate_t.h
.o/gl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gl.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/gl.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
.o/gl.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gl.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gl.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gl.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_math.h
.o/gl.o: /usr/include/math.h my_tile.h my_tex.h
.o/hexdump.o: /usr/include/string.h /usr/include/_types.h
.o/hexdump.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/hexdump.o: /usr/include/sys/_symbol_aliasing.h
.o/hexdump.o: /usr/include/sys/_posix_availability.h
.o/hexdump.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/hexdump.o: /usr/include/sys/_pthread/_pthread_types.h
.o/hexdump.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/hexdump.o: /usr/include/sys/_types/_size_t.h
.o/hexdump.o: /usr/include/sys/_types/_null.h
.o/hexdump.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/hexdump.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/hexdump.o: /usr/include/sys/_types/_int16_t.h
.o/hexdump.o: /usr/include/sys/_types/_int32_t.h
.o/hexdump.o: /usr/include/sys/_types/_int64_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int8_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int16_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int32_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int64_t.h
.o/hexdump.o: /usr/include/sys/_types/_intptr_t.h
.o/hexdump.o: /usr/include/sys/_types/_uintptr_t.h
.o/hexdump.o: /usr/include/sys/_types/_errno_t.h
.o/hexdump.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/hexdump.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/hexdump.o: /usr/include/secure/_string.h
.o/log.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/log.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/log.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/log.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/log.o: /usr/include/i386/_types.h
.o/log.o: /usr/include/sys/_pthread/_pthread_types.h
.o/log.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/log.o: /usr/include/sys/_types/_int8_t.h
.o/log.o: /usr/include/sys/_types/_int16_t.h
.o/log.o: /usr/include/sys/_types/_int32_t.h
.o/log.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/log.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/log.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/log.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/log.o: /usr/include/sys/_types/_u_int8_t.h
.o/log.o: /usr/include/sys/_types/_u_int16_t.h
.o/log.o: /usr/include/sys/_types/_u_int32_t.h
.o/log.o: /usr/include/sys/_types/_u_int64_t.h
.o/log.o: /usr/include/sys/_types/_uintptr_t.h
.o/log.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/log.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/log.o: /usr/include/sys/_types/_va_list.h
.o/log.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/log.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/log.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/log.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/log.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/log.o: /usr/include/sys/_types/_mbstate_t.h
.o/log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/log.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/log.o: /usr/include/sys/_types/_clock_t.h
.o/log.o: /usr/include/sys/_types/_time_t.h
.o/log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/log.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_time.h
.o/log.o: /usr/include/assert.h /usr/include/unistd.h
.o/log.o: /usr/include/sys/unistd.h /usr/include/sys/_types/_posix_vdisable.h
.o/log.o: /usr/include/sys/_types/_seek_set.h
.o/log.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/log.o: /usr/include/sys/_types/_pid_t.h
.o/log.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/log.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/log.o: /usr/include/sys/_types/_timeval.h
.o/log.o: /usr/include/sys/_types/_suseconds_t.h
.o/log.o: /usr/include/sys/_types/_sigset_t.h
.o/log.o: /usr/include/sys/_types/_fd_setsize.h
.o/log.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/log.o: /usr/include/sys/_types/_fd_isset.h
.o/log.o: /usr/include/sys/_types/_fd_zero.h
.o/log.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/log.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/log.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/log.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/log.o: my_traceback.h my_wid.h my_wid_tiles.h my_tile.h my_tex.h my_gl.h
.o/log.o: my_color.h my_point.h my_math.h /usr/include/math.h my_size.h
.o/log.o: my_wid_console.h my_wid_minicon.h my_console.h my_ascii.h
.o/main.o: /usr/include/libgen.h /usr/include/sys/cdefs.h
.o/main.o: /usr/include/sys/_symbol_aliasing.h
.o/main.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/main.o: /usr/include/AvailabilityInternal.h /usr/include/signal.h
.o/main.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/main.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/main.o: /usr/include/sys/_pthread/_pthread_types.h
.o/main.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/main.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/main.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/main.o: /usr/include/mach/machine/_structs.h
.o/main.o: /usr/include/mach/i386/_structs.h /usr/include/machine/types.h
.o/main.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/main.o: /usr/include/sys/_types/_int16_t.h
.o/main.o: /usr/include/sys/_types/_int32_t.h
.o/main.o: /usr/include/sys/_types/_int64_t.h
.o/main.o: /usr/include/sys/_types/_u_int8_t.h
.o/main.o: /usr/include/sys/_types/_u_int16_t.h
.o/main.o: /usr/include/sys/_types/_u_int32_t.h
.o/main.o: /usr/include/sys/_types/_u_int64_t.h
.o/main.o: /usr/include/sys/_types/_intptr_t.h
.o/main.o: /usr/include/sys/_types/_uintptr_t.h
.o/main.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/main.o: /usr/include/sys/_types/_sigaltstack.h
.o/main.o: /usr/include/sys/_types/_ucontext.h
.o/main.o: /usr/include/sys/_types/_pid_t.h
.o/main.o: /usr/include/sys/_types/_sigset_t.h
.o/main.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
.o/main.o: /usr/include/sys/_pthread/_pthread_t.h /usr/include/unistd.h
.o/main.o: /usr/include/sys/unistd.h
.o/main.o: /usr/include/sys/_types/_posix_vdisable.h
.o/main.o: /usr/include/sys/_types/_seek_set.h
.o/main.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_uint32_t.h
.o/main.o: /usr/include/sys/_types/_ssize_t.h
.o/main.o: /usr/include/sys/_types/_gid_t.h /usr/include/sys/_types/_off_t.h
.o/main.o: /usr/include/sys/_types/_useconds_t.h
.o/main.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/main.o: /usr/include/sys/_types/_fd_def.h
.o/main.o: /usr/include/sys/_types/_timespec.h
.o/main.o: /usr/include/sys/_types/_timeval.h
.o/main.o: /usr/include/sys/_types/_time_t.h
.o/main.o: /usr/include/sys/_types/_suseconds_t.h
.o/main.o: /usr/include/sys/_types/_fd_setsize.h
.o/main.o: /usr/include/sys/_types/_fd_set.h
.o/main.o: /usr/include/sys/_types/_fd_clr.h
.o/main.o: /usr/include/sys/_types/_fd_isset.h
.o/main.o: /usr/include/sys/_types/_fd_zero.h
.o/main.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/main.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/main.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/main.o: /usr/include/sys/stat.h /usr/include/sys/_types/_blkcnt_t.h
.o/main.o: /usr/include/sys/_types/_blksize_t.h
.o/main.o: /usr/include/sys/_types/_ino_t.h
.o/main.o: /usr/include/sys/_types/_ino64_t.h
.o/main.o: /usr/include/sys/_types/_nlink_t.h
.o/main.o: /usr/include/sys/_types/_s_ifmt.h
.o/main.o: /usr/include/sys/_types/_filesec_t.h my_main.h my_pcg_basic.h
.o/main.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/main.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/main.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_intmax_t.h
.o/main.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/main.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/main.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/main.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/main.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/main.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/main.o: my_token.h my_string.h /usr/include/wchar.h
.o/main.o: /usr/include/sys/_types/_mbstate_t.h
.o/main.o: /usr/include/sys/_types/_ct_rune_t.h
.o/main.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/main.o: /usr/include/sys/_types/_clock_t.h /usr/include/_wctype.h
.o/main.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/main.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/main.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_gl.h
.o/main.o: my_color.h my_point.h my_math.h /usr/include/math.h
.o/main.o: my_wid_console.h my_wid.h my_wid_tiles.h my_tile.h my_tex.h
.o/main.o: my_size.h my_wid_minicon.h my_wid_test.h my_font.h my_dir.h
.o/main.o: my_file.h my_traceback.h my_ascii.h my_gfx.h
.o/minilzo.o: /usr/include/limits.h /usr/include/sys/cdefs.h
.o/minilzo.o: /usr/include/sys/_symbol_aliasing.h
.o/minilzo.o: /usr/include/sys/_posix_availability.h
.o/minilzo.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
.o/minilzo.o: /usr/include/i386/_limits.h /usr/include/sys/syslimits.h
.o/minilzo.o: /usr/include/stddef.h /usr/include/_types.h
.o/minilzo.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/minilzo.o: /usr/include/i386/_types.h
.o/minilzo.o: /usr/include/sys/_pthread/_pthread_types.h
.o/minilzo.o: /usr/include/sys/_types/_null.h
.o/minilzo.o: /usr/include/sys/_types/_offsetof.h
.o/minilzo.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/minilzo.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/minilzo.o: /usr/include/sys/_types/_int8_t.h
.o/minilzo.o: /usr/include/sys/_types/_int16_t.h
.o/minilzo.o: /usr/include/sys/_types/_int32_t.h
.o/minilzo.o: /usr/include/sys/_types/_int64_t.h
.o/minilzo.o: /usr/include/sys/_types/_u_int8_t.h
.o/minilzo.o: /usr/include/sys/_types/_u_int16_t.h
.o/minilzo.o: /usr/include/sys/_types/_u_int32_t.h
.o/minilzo.o: /usr/include/sys/_types/_u_int64_t.h
.o/minilzo.o: /usr/include/sys/_types/_intptr_t.h
.o/minilzo.o: /usr/include/sys/_types/_uintptr_t.h
.o/minilzo.o: /usr/include/sys/_types/_rsize_t.h
.o/minilzo.o: /usr/include/sys/_types/_size_t.h
.o/minilzo.o: /usr/include/sys/_types/_wchar_t.h
.o/minilzo.o: /usr/include/sys/_types/_wint_t.h minilzo.h lzodefs.h lzoconf.h
.o/minilzo.o: /usr/include/string.h /usr/include/Availability.h
.o/minilzo.o: /usr/include/AvailabilityInternal.h
.o/minilzo.o: /usr/include/sys/_types/_errno_t.h
.o/minilzo.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/minilzo.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/minilzo.o: /usr/include/secure/_string.h /usr/include/assert.h
.o/pcg_basic.o: my_pcg_basic.h /usr/include/inttypes.h
.o/pcg_basic.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/pcg_basic.o: /usr/include/sys/_posix_availability.h
.o/pcg_basic.o: /usr/include/Availability.h
.o/pcg_basic.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/pcg_basic.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/pcg_basic.o: /usr/include/i386/_types.h
.o/pcg_basic.o: /usr/include/sys/_pthread/_pthread_types.h
.o/pcg_basic.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/pcg_basic.o: /usr/include/sys/_types/_int8_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_int16_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_int32_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_int64_t.h
.o/pcg_basic.o: /usr/include/_types/_uint8_t.h
.o/pcg_basic.o: /usr/include/_types/_uint16_t.h
.o/pcg_basic.o: /usr/include/_types/_uint32_t.h
.o/pcg_basic.o: /usr/include/_types/_uint64_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_intptr_t.h
.o/pcg_basic.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/pcg_basic.o: /usr/include/sys/_types/_u_int8_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_u_int16_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_u_int32_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_u_int64_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_uintptr_t.h
.o/pcg_basic.o: /usr/include/_types/_intmax_t.h
.o/pcg_basic.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
.o/pcg_basic.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/pcg_basic.o: /usr/include/sys/_types/_size_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/pcg_basic.o: /usr/include/sys/_types/_off_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_ssize_t.h
.o/pcg_basic.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ptrcheck.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/ptrcheck.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/ptrcheck.o: /usr/include/sys/_posix_availability.h
.o/ptrcheck.o: /usr/include/Availability.h
.o/ptrcheck.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ptrcheck.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ptrcheck.o: /usr/include/i386/_types.h
.o/ptrcheck.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ptrcheck.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/ptrcheck.o: /usr/include/sys/_types/_int8_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int16_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int32_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int64_t.h
.o/ptrcheck.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/ptrcheck.o: /usr/include/_types/_uint32_t.h
.o/ptrcheck.o: /usr/include/_types/_uint64_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_intptr_t.h
.o/ptrcheck.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int8_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int16_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int32_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int64_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_uintptr_t.h
.o/ptrcheck.o: /usr/include/_types/_intmax_t.h
.o/ptrcheck.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/ptrcheck.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/ptrcheck.o: /usr/include/sys/_types/_va_list.h
.o/ptrcheck.o: /usr/include/sys/_types/_size_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/ptrcheck.o: /usr/include/sys/_types/_off_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_ssize_t.h
.o/ptrcheck.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ptrcheck.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/ptrcheck.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/ptrcheck.o: my_token.h my_string.h /usr/include/wchar.h
.o/ptrcheck.o: /usr/include/sys/_types/_mbstate_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/ptrcheck.o: /usr/include/sys/_types/_clock_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_time_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ptrcheck.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/ptrcheck.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ptrcheck.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/ptrcheck.o: my_traceback.h my_sprintf.h /usr/include/string.h
.o/ptrcheck.o: /usr/include/sys/_types/_rsize_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ptrcheck.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/ptrcheck.o: my_time.h /usr/include/assert.h /usr/include/unistd.h
.o/ptrcheck.o: /usr/include/sys/unistd.h
.o/ptrcheck.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ptrcheck.o: /usr/include/sys/_types/_seek_set.h
.o/ptrcheck.o: /usr/include/sys/_types/_uid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_gid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_pid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_useconds_t.h
.o/ptrcheck.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_def.h
.o/ptrcheck.o: /usr/include/sys/_types/_timeval.h
.o/ptrcheck.o: /usr/include/sys/_types/_suseconds_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_sigset_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_setsize.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_set.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_clr.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_isset.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_zero.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ptrcheck.o: /usr/include/sys/_types/_dev_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_mode_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ptrcheck.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/sdl.o: my_gl.h my_color.h c_plus_plus_serializer.h my_point.h my_main.h
.o/sdl.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/sdl.o: /usr/include/sys/_symbol_aliasing.h
.o/sdl.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/sdl.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/sdl.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/sdl.o: /usr/include/i386/_types.h
.o/sdl.o: /usr/include/sys/_pthread/_pthread_types.h
.o/sdl.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/sdl.o: /usr/include/sys/_types/_int8_t.h
.o/sdl.o: /usr/include/sys/_types/_int16_t.h
.o/sdl.o: /usr/include/sys/_types/_int32_t.h
.o/sdl.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/sdl.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/sdl.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/sdl.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/sdl.o: /usr/include/sys/_types/_u_int8_t.h
.o/sdl.o: /usr/include/sys/_types/_u_int16_t.h
.o/sdl.o: /usr/include/sys/_types/_u_int32_t.h
.o/sdl.o: /usr/include/sys/_types/_u_int64_t.h
.o/sdl.o: /usr/include/sys/_types/_uintptr_t.h
.o/sdl.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/sdl.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/sdl.o: /usr/include/sys/_types/_va_list.h
.o/sdl.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/sdl.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/sdl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/sdl.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/sdl.o: my_vector_bounds_check.h my_ptrcheck.h my_sdl.h my_command.h
.o/sdl.o: my_token.h my_string.h /usr/include/wchar.h
.o/sdl.o: /usr/include/sys/_types/_mbstate_t.h
.o/sdl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/sdl.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/sdl.o: /usr/include/sys/_types/_clock_t.h
.o/sdl.o: /usr/include/sys/_types/_time_t.h
.o/sdl.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/sdl.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/sdl.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/sdl.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_math.h
.o/sdl.o: /usr/include/math.h my_wid.h my_wid_tiles.h my_tile.h my_tex.h
.o/sdl.o: my_size.h my_ascii.h my_time.h /usr/include/assert.h
.o/sdl.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/sdl.o: /usr/include/sys/_types/_posix_vdisable.h
.o/sdl.o: /usr/include/sys/_types/_seek_set.h
.o/sdl.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/sdl.o: /usr/include/sys/_types/_pid_t.h
.o/sdl.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/sdl.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/sdl.o: /usr/include/sys/_types/_timeval.h
.o/sdl.o: /usr/include/sys/_types/_suseconds_t.h
.o/sdl.o: /usr/include/sys/_types/_sigset_t.h
.o/sdl.o: /usr/include/sys/_types/_fd_setsize.h
.o/sdl.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/sdl.o: /usr/include/sys/_types/_fd_isset.h
.o/sdl.o: /usr/include/sys/_types/_fd_zero.h
.o/sdl.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/sdl.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/sdl.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/sdl.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/sdl.o: my_wid_console.h
.o/slre.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/slre.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/slre.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/slre.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/slre.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/slre.o: /usr/include/i386/_types.h
.o/slre.o: /usr/include/sys/_pthread/_pthread_types.h
.o/slre.o: /usr/include/sys/_types/_va_list.h /usr/include/machine/types.h
.o/slre.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/slre.o: /usr/include/sys/_types/_int16_t.h
.o/slre.o: /usr/include/sys/_types/_int32_t.h
.o/slre.o: /usr/include/sys/_types/_int64_t.h
.o/slre.o: /usr/include/sys/_types/_u_int8_t.h
.o/slre.o: /usr/include/sys/_types/_u_int16_t.h
.o/slre.o: /usr/include/sys/_types/_u_int32_t.h
.o/slre.o: /usr/include/sys/_types/_u_int64_t.h
.o/slre.o: /usr/include/sys/_types/_intptr_t.h
.o/slre.o: /usr/include/sys/_types/_uintptr_t.h
.o/slre.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/slre.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/slre.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/slre.o: /usr/include/secure/_common.h /usr/include/assert.h
.o/slre.o: /usr/include/ctype.h /usr/include/_ctype.h /usr/include/runetype.h
.o/slre.o: /usr/include/sys/_types/_ct_rune_t.h
.o/slre.o: /usr/include/sys/_types/_rune_t.h
.o/slre.o: /usr/include/sys/_types/_wchar_t.h
.o/slre.o: /usr/include/sys/_types/_wint_t.h /usr/include/string.h
.o/slre.o: /usr/include/sys/_types/_rsize_t.h
.o/slre.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/slre.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/slre.o: my_slre.h
.o/sprintf.o: my_sprintf.h /usr/include/string.h /usr/include/_types.h
.o/sprintf.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/sprintf.o: /usr/include/sys/_symbol_aliasing.h
.o/sprintf.o: /usr/include/sys/_posix_availability.h
.o/sprintf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/sprintf.o: /usr/include/sys/_pthread/_pthread_types.h
.o/sprintf.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/sprintf.o: /usr/include/sys/_types/_size_t.h
.o/sprintf.o: /usr/include/sys/_types/_null.h
.o/sprintf.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/sprintf.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/sprintf.o: /usr/include/sys/_types/_int16_t.h
.o/sprintf.o: /usr/include/sys/_types/_int32_t.h
.o/sprintf.o: /usr/include/sys/_types/_int64_t.h
.o/sprintf.o: /usr/include/sys/_types/_u_int8_t.h
.o/sprintf.o: /usr/include/sys/_types/_u_int16_t.h
.o/sprintf.o: /usr/include/sys/_types/_u_int32_t.h
.o/sprintf.o: /usr/include/sys/_types/_u_int64_t.h
.o/sprintf.o: /usr/include/sys/_types/_intptr_t.h
.o/sprintf.o: /usr/include/sys/_types/_uintptr_t.h
.o/sprintf.o: /usr/include/sys/_types/_errno_t.h
.o/sprintf.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/sprintf.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/sprintf.o: /usr/include/secure/_string.h /usr/include/stdio.h
.o/sprintf.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/sprintf.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/sprintf.o: /usr/include/secure/_stdio.h /usr/include/stdlib.h
.o/sprintf.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/sprintf.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/sprintf.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/sprintf.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/sprintf.o: /usr/include/i386/_mcontext.h
.o/sprintf.o: /usr/include/mach/machine/_structs.h
.o/sprintf.o: /usr/include/mach/i386/_structs.h
.o/sprintf.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/sprintf.o: /usr/include/sys/_types/_sigaltstack.h
.o/sprintf.o: /usr/include/sys/_types/_ucontext.h
.o/sprintf.o: /usr/include/sys/_types/_sigset_t.h
.o/sprintf.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/sprintf.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/sprintf.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/sprintf.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/sprintf.o: /usr/include/_types/_uintmax_t.h
.o/sprintf.o: /usr/include/sys/_types/_timeval.h
.o/sprintf.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/sprintf.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/sprintf.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/sprintf.o: /usr/include/sys/_types/_ct_rune_t.h
.o/sprintf.o: /usr/include/sys/_types/_rune_t.h
.o/sprintf.o: /usr/include/sys/_types/_wchar_t.h
.o/sprintf.o: /usr/include/sys/_types/_dev_t.h
.o/sprintf.o: /usr/include/sys/_types/_mode_t.h
.o/stb_image.o: stb_image.h /usr/include/stdio.h /usr/include/_stdio.h
.o/stb_image.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/stb_image.o: /usr/include/sys/_posix_availability.h
.o/stb_image.o: /usr/include/Availability.h
.o/stb_image.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/stb_image.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/stb_image.o: /usr/include/i386/_types.h
.o/stb_image.o: /usr/include/sys/_pthread/_pthread_types.h
.o/stb_image.o: /usr/include/sys/_types/_va_list.h
.o/stb_image.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/stb_image.o: /usr/include/sys/_types/_int8_t.h
.o/stb_image.o: /usr/include/sys/_types/_int16_t.h
.o/stb_image.o: /usr/include/sys/_types/_int32_t.h
.o/stb_image.o: /usr/include/sys/_types/_int64_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int8_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int16_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int32_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int64_t.h
.o/stb_image.o: /usr/include/sys/_types/_intptr_t.h
.o/stb_image.o: /usr/include/sys/_types/_uintptr_t.h
.o/stb_image.o: /usr/include/sys/_types/_size_t.h
.o/stb_image.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/stb_image.o: /usr/include/sys/_types/_off_t.h
.o/stb_image.o: /usr/include/sys/_types/_ssize_t.h
.o/stb_image.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/stb_image.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/stb_image.o: /usr/include/sys/_types/_pid_t.h
.o/stb_image.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/stb_image.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/stb_image.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/stb_image.o: /usr/include/i386/_mcontext.h
.o/stb_image.o: /usr/include/mach/machine/_structs.h
.o/stb_image.o: /usr/include/mach/i386/_structs.h
.o/stb_image.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/stb_image.o: /usr/include/sys/_types/_sigaltstack.h
.o/stb_image.o: /usr/include/sys/_types/_ucontext.h
.o/stb_image.o: /usr/include/sys/_types/_sigset_t.h
.o/stb_image.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/stb_image.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/stb_image.o: /usr/include/_types/_uint16_t.h
.o/stb_image.o: /usr/include/_types/_uint32_t.h
.o/stb_image.o: /usr/include/_types/_uint64_t.h
.o/stb_image.o: /usr/include/_types/_intmax_t.h
.o/stb_image.o: /usr/include/_types/_uintmax_t.h
.o/stb_image.o: /usr/include/sys/_types/_timeval.h
.o/stb_image.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/stb_image.o: /usr/include/sys/_endian.h
.o/stb_image.o: /usr/include/libkern/_OSByteOrder.h
.o/stb_image.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/stb_image.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/stb_image.o: /usr/include/sys/_types/_rune_t.h
.o/stb_image.o: /usr/include/sys/_types/_wchar_t.h
.o/stb_image.o: /usr/include/sys/_types/_dev_t.h
.o/stb_image.o: /usr/include/sys/_types/_mode_t.h /usr/include/stddef.h
.o/stb_image.o: /usr/include/sys/_types/_offsetof.h
.o/stb_image.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/stb_image.o: /usr/include/sys/_types/_rsize_t.h
.o/stb_image.o: /usr/include/sys/_types/_wint_t.h /usr/include/string.h
.o/stb_image.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/stb_image.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/stb_image.o: /usr/include/limits.h /usr/include/machine/limits.h
.o/stb_image.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
.o/stb_image.o: /usr/include/sys/syslimits.h /usr/include/math.h
.o/stb_image.o: /usr/include/assert.h stb_image_write.h
.o/string.o: /usr/include/libgen.h /usr/include/sys/cdefs.h
.o/string.o: /usr/include/sys/_symbol_aliasing.h
.o/string.o: /usr/include/sys/_posix_availability.h
.o/string.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/string.o: /usr/include/time.h /usr/include/_types.h
.o/string.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/string.o: /usr/include/i386/_types.h
.o/string.o: /usr/include/sys/_pthread/_pthread_types.h
.o/string.o: /usr/include/sys/_types/_clock_t.h /usr/include/machine/types.h
.o/string.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/string.o: /usr/include/sys/_types/_int16_t.h
.o/string.o: /usr/include/sys/_types/_int32_t.h
.o/string.o: /usr/include/sys/_types/_int64_t.h
.o/string.o: /usr/include/sys/_types/_u_int8_t.h
.o/string.o: /usr/include/sys/_types/_u_int16_t.h
.o/string.o: /usr/include/sys/_types/_u_int32_t.h
.o/string.o: /usr/include/sys/_types/_u_int64_t.h
.o/string.o: /usr/include/sys/_types/_intptr_t.h
.o/string.o: /usr/include/sys/_types/_uintptr_t.h
.o/string.o: /usr/include/sys/_types/_null.h
.o/string.o: /usr/include/sys/_types/_size_t.h
.o/string.o: /usr/include/sys/_types/_time_t.h
.o/string.o: /usr/include/sys/_types/_timespec.h my_main.h my_pcg_basic.h
.o/string.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/string.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/string.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/string.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/string.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/string.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/string.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/string.o: /usr/include/sys/_types/_off_t.h
.o/string.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/string.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/string.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/string.o: my_sdl.h my_command.h my_token.h my_string.h
.o/string.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/string.o: /usr/include/sys/_types/_ct_rune_t.h
.o/string.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/string.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/string.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/string.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_tex.h
.o/string.o: my_color.h my_time.h /usr/include/assert.h /usr/include/unistd.h
.o/string.o: /usr/include/sys/unistd.h
.o/string.o: /usr/include/sys/_types/_posix_vdisable.h
.o/string.o: /usr/include/sys/_types/_seek_set.h
.o/string.o: /usr/include/sys/_types/_uid_t.h
.o/string.o: /usr/include/sys/_types/_gid_t.h
.o/string.o: /usr/include/sys/_types/_pid_t.h
.o/string.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/string.o: /usr/include/sys/appleapiopts.h
.o/string.o: /usr/include/sys/_types/_fd_def.h
.o/string.o: /usr/include/sys/_types/_timeval.h
.o/string.o: /usr/include/sys/_types/_suseconds_t.h
.o/string.o: /usr/include/sys/_types/_sigset_t.h
.o/string.o: /usr/include/sys/_types/_fd_setsize.h
.o/string.o: /usr/include/sys/_types/_fd_set.h
.o/string.o: /usr/include/sys/_types/_fd_clr.h
.o/string.o: /usr/include/sys/_types/_fd_isset.h
.o/string.o: /usr/include/sys/_types/_fd_zero.h
.o/string.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/string.o: /usr/include/sys/_types/_dev_t.h
.o/string.o: /usr/include/sys/_types/_mode_t.h
.o/string.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/string.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/string.o: my_tile.h my_gl.h my_point.h my_math.h /usr/include/math.h
.o/tex.o: stb_image.h /usr/include/stdio.h /usr/include/_stdio.h
.o/tex.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/tex.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/tex.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/tex.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/tex.o: /usr/include/i386/_types.h
.o/tex.o: /usr/include/sys/_pthread/_pthread_types.h
.o/tex.o: /usr/include/sys/_types/_va_list.h /usr/include/machine/types.h
.o/tex.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/tex.o: /usr/include/sys/_types/_int16_t.h
.o/tex.o: /usr/include/sys/_types/_int32_t.h
.o/tex.o: /usr/include/sys/_types/_int64_t.h
.o/tex.o: /usr/include/sys/_types/_u_int8_t.h
.o/tex.o: /usr/include/sys/_types/_u_int16_t.h
.o/tex.o: /usr/include/sys/_types/_u_int32_t.h
.o/tex.o: /usr/include/sys/_types/_u_int64_t.h
.o/tex.o: /usr/include/sys/_types/_intptr_t.h
.o/tex.o: /usr/include/sys/_types/_uintptr_t.h
.o/tex.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/tex.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/tex.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/tex.o: /usr/include/secure/_common.h /usr/include/stdlib.h
.o/tex.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/tex.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/tex.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/tex.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/tex.o: /usr/include/i386/_mcontext.h /usr/include/mach/machine/_structs.h
.o/tex.o: /usr/include/mach/i386/_structs.h
.o/tex.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/tex.o: /usr/include/sys/_types/_sigaltstack.h
.o/tex.o: /usr/include/sys/_types/_ucontext.h
.o/tex.o: /usr/include/sys/_types/_sigset_t.h
.o/tex.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/tex.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/tex.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/tex.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/tex.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
.o/tex.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/tex.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/tex.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/tex.o: /usr/include/sys/_types/_ct_rune_t.h
.o/tex.o: /usr/include/sys/_types/_rune_t.h
.o/tex.o: /usr/include/sys/_types/_wchar_t.h /usr/include/sys/_types/_dev_t.h
.o/tex.o: /usr/include/sys/_types/_mode_t.h /usr/include/stddef.h
.o/tex.o: /usr/include/sys/_types/_offsetof.h
.o/tex.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/tex.o: /usr/include/sys/_types/_rsize_t.h
.o/tex.o: /usr/include/sys/_types/_wint_t.h /usr/include/string.h
.o/tex.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/tex.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/tex.o: /usr/include/limits.h /usr/include/machine/limits.h
.o/tex.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
.o/tex.o: /usr/include/sys/syslimits.h /usr/include/math.h
.o/tex.o: /usr/include/assert.h my_gl.h my_color.h c_plus_plus_serializer.h
.o/tex.o: my_point.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/tex.o: my_callstack.h my_array_bounds_check.h my_vector_bounds_check.h
.o/tex.o: my_ptrcheck.h my_sdl.h my_command.h my_token.h my_string.h
.o/tex.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/tex.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/tex.o: /usr/include/sys/_types/_time_t.h
.o/tex.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/tex.o: /usr/include/__wctype.h /usr/include/_types/_wctype_t.h
.o/tex.o: /usr/include/ctype.h /usr/include/_ctype.h /usr/include/runetype.h
.o/tex.o: my_slre.h my_math.h my_tex.h my_ramdisk.h my_pixel.h
.o/tile.o: my_gl.h my_color.h c_plus_plus_serializer.h my_point.h my_main.h
.o/tile.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/tile.o: /usr/include/sys/_symbol_aliasing.h
.o/tile.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/tile.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/tile.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/tile.o: /usr/include/i386/_types.h
.o/tile.o: /usr/include/sys/_pthread/_pthread_types.h
.o/tile.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/tile.o: /usr/include/sys/_types/_int8_t.h
.o/tile.o: /usr/include/sys/_types/_int16_t.h
.o/tile.o: /usr/include/sys/_types/_int32_t.h
.o/tile.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/tile.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/tile.o: /usr/include/_types/_uint64_t.h
.o/tile.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/tile.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/tile.o: /usr/include/sys/_types/_u_int16_t.h
.o/tile.o: /usr/include/sys/_types/_u_int32_t.h
.o/tile.o: /usr/include/sys/_types/_u_int64_t.h
.o/tile.o: /usr/include/sys/_types/_uintptr_t.h
.o/tile.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/tile.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/tile.o: /usr/include/sys/_types/_va_list.h
.o/tile.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/tile.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/tile.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/tile.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/tile.o: my_vector_bounds_check.h my_ptrcheck.h my_sdl.h my_command.h
.o/tile.o: my_token.h my_string.h /usr/include/wchar.h
.o/tile.o: /usr/include/sys/_types/_mbstate_t.h
.o/tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/tile.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/tile.o: /usr/include/sys/_types/_clock_t.h
.o/tile.o: /usr/include/sys/_types/_time_t.h
.o/tile.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/tile.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/tile.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/tile.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_math.h
.o/tile.o: /usr/include/math.h my_tile.h my_tex.h my_pixel.h my_size.h
.o/time.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/time.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/time.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/time.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/time.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/time.o: /usr/include/i386/_types.h
.o/time.o: /usr/include/sys/_pthread/_pthread_types.h
.o/time.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/time.o: /usr/include/sys/_types/_int8_t.h
.o/time.o: /usr/include/sys/_types/_int16_t.h
.o/time.o: /usr/include/sys/_types/_int32_t.h
.o/time.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/time.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/time.o: /usr/include/_types/_uint64_t.h
.o/time.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/time.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/time.o: /usr/include/sys/_types/_u_int16_t.h
.o/time.o: /usr/include/sys/_types/_u_int32_t.h
.o/time.o: /usr/include/sys/_types/_u_int64_t.h
.o/time.o: /usr/include/sys/_types/_uintptr_t.h
.o/time.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/time.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/time.o: /usr/include/sys/_types/_va_list.h
.o/time.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/time.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/time.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/time.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/time.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/time.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/time.o: /usr/include/sys/_types/_mbstate_t.h
.o/time.o: /usr/include/sys/_types/_ct_rune_t.h
.o/time.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/time.o: /usr/include/sys/_types/_clock_t.h
.o/time.o: /usr/include/sys/_types/_time_t.h
.o/time.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/time.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/time.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/time.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_time.h
.o/time.o: /usr/include/assert.h /usr/include/unistd.h
.o/time.o: /usr/include/sys/unistd.h
.o/time.o: /usr/include/sys/_types/_posix_vdisable.h
.o/time.o: /usr/include/sys/_types/_seek_set.h
.o/time.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/time.o: /usr/include/sys/_types/_pid_t.h
.o/time.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/time.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/time.o: /usr/include/sys/_types/_timeval.h
.o/time.o: /usr/include/sys/_types/_suseconds_t.h
.o/time.o: /usr/include/sys/_types/_sigset_t.h
.o/time.o: /usr/include/sys/_types/_fd_setsize.h
.o/time.o: /usr/include/sys/_types/_fd_set.h
.o/time.o: /usr/include/sys/_types/_fd_clr.h
.o/time.o: /usr/include/sys/_types/_fd_isset.h
.o/time.o: /usr/include/sys/_types/_fd_zero.h
.o/time.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/time.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/time.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/time.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/token.o: /usr/include/string.h /usr/include/_types.h
.o/token.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/token.o: /usr/include/sys/_symbol_aliasing.h
.o/token.o: /usr/include/sys/_posix_availability.h
.o/token.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/token.o: /usr/include/sys/_pthread/_pthread_types.h
.o/token.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/token.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/token.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/token.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/token.o: /usr/include/sys/_types/_int16_t.h
.o/token.o: /usr/include/sys/_types/_int32_t.h
.o/token.o: /usr/include/sys/_types/_int64_t.h
.o/token.o: /usr/include/sys/_types/_u_int8_t.h
.o/token.o: /usr/include/sys/_types/_u_int16_t.h
.o/token.o: /usr/include/sys/_types/_u_int32_t.h
.o/token.o: /usr/include/sys/_types/_u_int64_t.h
.o/token.o: /usr/include/sys/_types/_intptr_t.h
.o/token.o: /usr/include/sys/_types/_uintptr_t.h
.o/token.o: /usr/include/sys/_types/_errno_t.h
.o/token.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/token.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/token.o: /usr/include/secure/_string.h my_main.h my_pcg_basic.h
.o/token.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/token.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/token.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/token.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/token.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/token.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/token.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/token.o: /usr/include/sys/_types/_off_t.h /usr/include/secure/_stdio.h
.o/token.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/token.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/token.o: my_token.h my_string.h /usr/include/wchar.h
.o/token.o: /usr/include/sys/_types/_mbstate_t.h
.o/token.o: /usr/include/sys/_types/_ct_rune_t.h
.o/token.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/token.o: /usr/include/sys/_types/_clock_t.h
.o/token.o: /usr/include/sys/_types/_time_t.h
.o/token.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/token.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/token.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/token.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/traceback.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/traceback.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/traceback.o: /usr/include/sys/_posix_availability.h
.o/traceback.o: /usr/include/Availability.h
.o/traceback.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/traceback.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/traceback.o: /usr/include/i386/_types.h
.o/traceback.o: /usr/include/sys/_pthread/_pthread_types.h
.o/traceback.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/traceback.o: /usr/include/sys/_types/_int8_t.h
.o/traceback.o: /usr/include/sys/_types/_int16_t.h
.o/traceback.o: /usr/include/sys/_types/_int32_t.h
.o/traceback.o: /usr/include/sys/_types/_int64_t.h
.o/traceback.o: /usr/include/_types/_uint8_t.h
.o/traceback.o: /usr/include/_types/_uint16_t.h
.o/traceback.o: /usr/include/_types/_uint32_t.h
.o/traceback.o: /usr/include/_types/_uint64_t.h
.o/traceback.o: /usr/include/sys/_types/_intptr_t.h
.o/traceback.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/traceback.o: /usr/include/sys/_types/_u_int8_t.h
.o/traceback.o: /usr/include/sys/_types/_u_int16_t.h
.o/traceback.o: /usr/include/sys/_types/_u_int32_t.h
.o/traceback.o: /usr/include/sys/_types/_u_int64_t.h
.o/traceback.o: /usr/include/sys/_types/_uintptr_t.h
.o/traceback.o: /usr/include/_types/_intmax_t.h
.o/traceback.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/traceback.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/traceback.o: /usr/include/sys/_types/_va_list.h
.o/traceback.o: /usr/include/sys/_types/_size_t.h
.o/traceback.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/traceback.o: /usr/include/sys/_types/_off_t.h
.o/traceback.o: /usr/include/sys/_types/_ssize_t.h
.o/traceback.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/traceback.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/traceback.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/traceback.o: my_token.h my_string.h /usr/include/wchar.h
.o/traceback.o: /usr/include/sys/_types/_mbstate_t.h
.o/traceback.o: /usr/include/sys/_types/_ct_rune_t.h
.o/traceback.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/traceback.o: /usr/include/sys/_types/_clock_t.h
.o/traceback.o: /usr/include/sys/_types/_time_t.h
.o/traceback.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/traceback.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/traceback.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/traceback.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/traceback.o: my_traceback.h my_sprintf.h /usr/include/string.h
.o/traceback.o: /usr/include/sys/_types/_rsize_t.h
.o/traceback.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/traceback.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/traceback.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/traceback.o: /usr/include/sys/_types/_pid_t.h
.o/traceback.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/traceback.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/traceback.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/traceback.o: /usr/include/i386/_mcontext.h
.o/traceback.o: /usr/include/mach/machine/_structs.h
.o/traceback.o: /usr/include/mach/i386/_structs.h
.o/traceback.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/traceback.o: /usr/include/sys/_types/_sigaltstack.h
.o/traceback.o: /usr/include/sys/_types/_ucontext.h
.o/traceback.o: /usr/include/sys/_types/_sigset_t.h
.o/traceback.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/traceback.o: /usr/include/sys/_types/_timeval.h
.o/traceback.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/traceback.o: /usr/include/sys/_endian.h
.o/traceback.o: /usr/include/libkern/_OSByteOrder.h
.o/traceback.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/traceback.o: /usr/include/alloca.h /usr/include/sys/_types/_dev_t.h
.o/traceback.o: /usr/include/sys/_types/_mode_t.h /usr/include/execinfo.h
.o/traceback.o: /usr/include/cxxabi.h /usr/include/stddef.h
.o/traceback.o: /usr/include/sys/_types/_offsetof.h
.o/traceback.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/traceback.o: /usr/include/__cxxabi_config.h
.o/ttf.o: my_gl.h my_color.h c_plus_plus_serializer.h my_point.h my_main.h
.o/ttf.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/ttf.o: /usr/include/sys/_symbol_aliasing.h
.o/ttf.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/ttf.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ttf.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ttf.o: /usr/include/i386/_types.h
.o/ttf.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ttf.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/ttf.o: /usr/include/sys/_types/_int8_t.h
.o/ttf.o: /usr/include/sys/_types/_int16_t.h
.o/ttf.o: /usr/include/sys/_types/_int32_t.h
.o/ttf.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/ttf.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/ttf.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/ttf.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ttf.o: /usr/include/sys/_types/_u_int8_t.h
.o/ttf.o: /usr/include/sys/_types/_u_int16_t.h
.o/ttf.o: /usr/include/sys/_types/_u_int32_t.h
.o/ttf.o: /usr/include/sys/_types/_u_int64_t.h
.o/ttf.o: /usr/include/sys/_types/_uintptr_t.h
.o/ttf.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/ttf.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/ttf.o: /usr/include/sys/_types/_va_list.h
.o/ttf.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/ttf.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/ttf.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/ttf.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/ttf.o: my_vector_bounds_check.h my_ptrcheck.h my_sdl.h my_command.h
.o/ttf.o: my_token.h my_string.h /usr/include/wchar.h
.o/ttf.o: /usr/include/sys/_types/_mbstate_t.h
.o/ttf.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ttf.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/ttf.o: /usr/include/sys/_types/_clock_t.h
.o/ttf.o: /usr/include/sys/_types/_time_t.h
.o/ttf.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ttf.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/ttf.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ttf.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_math.h
.o/ttf.o: /usr/include/math.h my_wid.h my_wid_tiles.h my_tile.h my_tex.h
.o/ttf.o: my_size.h my_ttf.h my_font.h my_ramdisk.h my_time.h
.o/ttf.o: /usr/include/assert.h /usr/include/unistd.h
.o/ttf.o: /usr/include/sys/unistd.h /usr/include/sys/_types/_posix_vdisable.h
.o/ttf.o: /usr/include/sys/_types/_seek_set.h
.o/ttf.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/ttf.o: /usr/include/sys/_types/_pid_t.h
.o/ttf.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/ttf.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/ttf.o: /usr/include/sys/_types/_timeval.h
.o/ttf.o: /usr/include/sys/_types/_suseconds_t.h
.o/ttf.o: /usr/include/sys/_types/_sigset_t.h
.o/ttf.o: /usr/include/sys/_types/_fd_setsize.h
.o/ttf.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/ttf.o: /usr/include/sys/_types/_fd_isset.h
.o/ttf.o: /usr/include/sys/_types/_fd_zero.h
.o/ttf.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ttf.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/ttf.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ttf.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/ttf.o: my_bits.h my_pixel.h stb_image.h /usr/include/stdlib.h
.o/ttf.o: /usr/include/sys/wait.h /usr/include/sys/_types/_id_t.h
.o/ttf.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
.o/ttf.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/ttf.o: /usr/include/i386/_mcontext.h /usr/include/mach/machine/_structs.h
.o/ttf.o: /usr/include/mach/i386/_structs.h
.o/ttf.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ttf.o: /usr/include/sys/_types/_sigaltstack.h
.o/ttf.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/resource.h
.o/ttf.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/ttf.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/ttf.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/ttf.o: /usr/include/stddef.h /usr/include/sys/_types/_offsetof.h
.o/ttf.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/ttf.o: /usr/include/sys/_types/_rsize_t.h /usr/include/string.h
.o/ttf.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ttf.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/ttf.o: /usr/include/limits.h /usr/include/machine/limits.h
.o/ttf.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
.o/ttf.o: /usr/include/sys/syslimits.h stb_image_write.h
.o/util.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/util.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/util.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/util.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/util.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/util.o: /usr/include/i386/_types.h
.o/util.o: /usr/include/sys/_pthread/_pthread_types.h
.o/util.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/util.o: /usr/include/sys/_types/_int8_t.h
.o/util.o: /usr/include/sys/_types/_int16_t.h
.o/util.o: /usr/include/sys/_types/_int32_t.h
.o/util.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/util.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/util.o: /usr/include/_types/_uint64_t.h
.o/util.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/util.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/util.o: /usr/include/sys/_types/_u_int16_t.h
.o/util.o: /usr/include/sys/_types/_u_int32_t.h
.o/util.o: /usr/include/sys/_types/_u_int64_t.h
.o/util.o: /usr/include/sys/_types/_uintptr_t.h
.o/util.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/util.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/util.o: /usr/include/sys/_types/_va_list.h
.o/util.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/util.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/util.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/util.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/util.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/util.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/util.o: /usr/include/sys/_types/_mbstate_t.h
.o/util.o: /usr/include/sys/_types/_ct_rune_t.h
.o/util.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/util.o: /usr/include/sys/_types/_clock_t.h
.o/util.o: /usr/include/sys/_types/_time_t.h
.o/util.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/util.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/util.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/util.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/util.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/util.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/util.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/util.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/util.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/util.o: /usr/include/mach/machine/_structs.h
.o/util.o: /usr/include/mach/i386/_structs.h
.o/util.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/util.o: /usr/include/sys/_types/_sigaltstack.h
.o/util.o: /usr/include/sys/_types/_ucontext.h
.o/util.o: /usr/include/sys/_types/_sigset_t.h
.o/util.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/util.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/util.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/util.o: /usr/include/libkern/_OSByteOrder.h
.o/util.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/util.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/util.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/util.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/util.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/wid.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/wid.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid.o: /usr/include/i386/_types.h
.o/wid.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid.o: /usr/include/sys/_types/_int8_t.h
.o/wid.o: /usr/include/sys/_types/_int16_t.h
.o/wid.o: /usr/include/sys/_types/_int32_t.h
.o/wid.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/wid.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/wid.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/wid.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/wid.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/wid.o: /usr/include/sys/_types/_va_list.h
.o/wid.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/wid.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/wid.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/wid.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_ptrcheck.h
.o/wid.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/wid.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid.o: /usr/include/sys/_types/_clock_t.h
.o/wid.o: /usr/include/sys/_types/_time_t.h
.o/wid.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_wid.h
.o/wid.o: my_wid_tiles.h my_tile.h my_tex.h my_gl.h my_color.h my_point.h
.o/wid.o: my_math.h /usr/include/math.h my_size.h my_time.h
.o/wid.o: /usr/include/assert.h /usr/include/unistd.h
.o/wid.o: /usr/include/sys/unistd.h /usr/include/sys/_types/_posix_vdisable.h
.o/wid.o: /usr/include/sys/_types/_seek_set.h
.o/wid.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/wid.o: /usr/include/sys/_types/_pid_t.h
.o/wid.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/wid.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/wid.o: /usr/include/sys/_types/_timeval.h
.o/wid.o: /usr/include/sys/_types/_suseconds_t.h
.o/wid.o: /usr/include/sys/_types/_sigset_t.h
.o/wid.o: /usr/include/sys/_types/_fd_setsize.h
.o/wid.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/wid.o: /usr/include/sys/_types/_fd_isset.h
.o/wid.o: /usr/include/sys/_types/_fd_zero.h
.o/wid.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/wid.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/wid.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/wid.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/wid.o: my_wid_console.h my_wid_minicon.h my_sprintf.h
.o/wid.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/wid.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/wid.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/wid.o: my_ascii.h /usr/include/stdlib.h /usr/include/sys/wait.h
.o/wid.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/wid.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/wid.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/wid.o: /usr/include/mach/machine/_structs.h
.o/wid.o: /usr/include/mach/i386/_structs.h
.o/wid.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/wid.o: /usr/include/sys/_types/_sigaltstack.h
.o/wid.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/resource.h
.o/wid.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/wid.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/wid.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/wid_console.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_console.o: /usr/include/sys/cdefs.h
.o/wid_console.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_console.o: /usr/include/sys/_posix_availability.h
.o/wid_console.o: /usr/include/Availability.h
.o/wid_console.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_console.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_console.o: /usr/include/i386/_types.h
.o/wid_console.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_console.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_console.o: /usr/include/sys/_types/_int8_t.h
.o/wid_console.o: /usr/include/sys/_types/_int16_t.h
.o/wid_console.o: /usr/include/sys/_types/_int32_t.h
.o/wid_console.o: /usr/include/sys/_types/_int64_t.h
.o/wid_console.o: /usr/include/_types/_uint8_t.h
.o/wid_console.o: /usr/include/_types/_uint16_t.h
.o/wid_console.o: /usr/include/_types/_uint32_t.h
.o/wid_console.o: /usr/include/_types/_uint64_t.h
.o/wid_console.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_console.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_console.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_console.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_console.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_console.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_console.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_console.o: /usr/include/_types/_intmax_t.h
.o/wid_console.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/wid_console.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_console.o: /usr/include/sys/_types/_va_list.h
.o/wid_console.o: /usr/include/sys/_types/_size_t.h
.o/wid_console.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_console.o: /usr/include/sys/_types/_off_t.h
.o/wid_console.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_console.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_console.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/wid_console.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h
.o/wid_console.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/wid_console.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_console.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_console.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_console.o: /usr/include/sys/_types/_clock_t.h
.o/wid_console.o: /usr/include/sys/_types/_time_t.h
.o/wid_console.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_console.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_console.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_console.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_console.o: my_wid_console.h my_wid.h my_wid_tiles.h my_tile.h my_tex.h
.o/wid_console.o: my_gl.h my_color.h my_point.h my_math.h /usr/include/math.h
.o/wid_console.o: my_size.h my_ttf.h my_font.h my_ascii.h
.o/wid_minicon.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_minicon.o: /usr/include/sys/cdefs.h
.o/wid_minicon.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_minicon.o: /usr/include/sys/_posix_availability.h
.o/wid_minicon.o: /usr/include/Availability.h
.o/wid_minicon.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_minicon.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_minicon.o: /usr/include/i386/_types.h
.o/wid_minicon.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_minicon.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_minicon.o: /usr/include/sys/_types/_int8_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_int16_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_int32_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_int64_t.h
.o/wid_minicon.o: /usr/include/_types/_uint8_t.h
.o/wid_minicon.o: /usr/include/_types/_uint16_t.h
.o/wid_minicon.o: /usr/include/_types/_uint32_t.h
.o/wid_minicon.o: /usr/include/_types/_uint64_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_minicon.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_minicon.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_minicon.o: /usr/include/_types/_intmax_t.h
.o/wid_minicon.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/wid_minicon.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_minicon.o: /usr/include/sys/_types/_va_list.h
.o/wid_minicon.o: /usr/include/sys/_types/_size_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_minicon.o: /usr/include/sys/_types/_off_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_minicon.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_minicon.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/wid_minicon.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h
.o/wid_minicon.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/wid_minicon.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_minicon.o: /usr/include/sys/_types/_clock_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_time_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_minicon.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_minicon.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_minicon.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_minicon.o: my_wid_minicon.h my_wid.h my_wid_tiles.h my_tile.h my_tex.h
.o/wid_minicon.o: my_gl.h my_color.h my_point.h my_math.h /usr/include/math.h
.o/wid_minicon.o: my_size.h my_ttf.h my_font.h my_ascii.h
.o/wid_popup.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_popup.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid_popup.o: /usr/include/sys/_posix_availability.h
.o/wid_popup.o: /usr/include/Availability.h
.o/wid_popup.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_popup.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_popup.o: /usr/include/i386/_types.h
.o/wid_popup.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_popup.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_popup.o: /usr/include/sys/_types/_int8_t.h
.o/wid_popup.o: /usr/include/sys/_types/_int16_t.h
.o/wid_popup.o: /usr/include/sys/_types/_int32_t.h
.o/wid_popup.o: /usr/include/sys/_types/_int64_t.h
.o/wid_popup.o: /usr/include/_types/_uint8_t.h
.o/wid_popup.o: /usr/include/_types/_uint16_t.h
.o/wid_popup.o: /usr/include/_types/_uint32_t.h
.o/wid_popup.o: /usr/include/_types/_uint64_t.h
.o/wid_popup.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_popup.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_popup.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_popup.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_popup.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_popup.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_popup.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_popup.o: /usr/include/_types/_intmax_t.h
.o/wid_popup.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/wid_popup.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_popup.o: /usr/include/sys/_types/_va_list.h
.o/wid_popup.o: /usr/include/sys/_types/_size_t.h
.o/wid_popup.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_popup.o: /usr/include/sys/_types/_off_t.h
.o/wid_popup.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_popup.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_popup.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/wid_popup.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/wid_popup.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid_popup.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_popup.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_popup.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_popup.o: /usr/include/sys/_types/_clock_t.h
.o/wid_popup.o: /usr/include/sys/_types/_time_t.h
.o/wid_popup.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_popup.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_popup.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_popup.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_popup.o: my_wid_popup.h my_wid_text_box.h my_wid.h my_wid_tiles.h
.o/wid_popup.o: my_tile.h my_tex.h my_gl.h my_color.h my_point.h my_math.h
.o/wid_popup.o: /usr/include/math.h my_size.h my_ttf.h my_font.h my_ascii.h
.o/wid_test.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_test.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid_test.o: /usr/include/sys/_posix_availability.h
.o/wid_test.o: /usr/include/Availability.h
.o/wid_test.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_test.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_test.o: /usr/include/i386/_types.h
.o/wid_test.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_test.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_test.o: /usr/include/sys/_types/_int8_t.h
.o/wid_test.o: /usr/include/sys/_types/_int16_t.h
.o/wid_test.o: /usr/include/sys/_types/_int32_t.h
.o/wid_test.o: /usr/include/sys/_types/_int64_t.h
.o/wid_test.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/wid_test.o: /usr/include/_types/_uint32_t.h
.o/wid_test.o: /usr/include/_types/_uint64_t.h
.o/wid_test.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_test.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_test.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_test.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_test.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_test.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_test.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_test.o: /usr/include/_types/_intmax_t.h
.o/wid_test.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/wid_test.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_test.o: /usr/include/sys/_types/_va_list.h
.o/wid_test.o: /usr/include/sys/_types/_size_t.h
.o/wid_test.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_test.o: /usr/include/sys/_types/_off_t.h
.o/wid_test.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_test.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_test.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/wid_test.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/wid_test.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid_test.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_test.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_test.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_test.o: /usr/include/sys/_types/_clock_t.h
.o/wid_test.o: /usr/include/sys/_types/_time_t.h
.o/wid_test.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_test.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_test.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_test.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_test.o: my_wid_test.h my_wid.h my_wid_tiles.h my_tile.h my_tex.h
.o/wid_test.o: my_gl.h my_color.h my_point.h my_math.h /usr/include/math.h
.o/wid_test.o: my_size.h my_ttf.h my_font.h my_wid_popup.h my_wid_text_box.h
.o/wid_test.o: my_ascii.h
.o/wid_text_box.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_text_box.o: /usr/include/sys/cdefs.h
.o/wid_text_box.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_text_box.o: /usr/include/sys/_posix_availability.h
.o/wid_text_box.o: /usr/include/Availability.h
.o/wid_text_box.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_text_box.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_text_box.o: /usr/include/i386/_types.h
.o/wid_text_box.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_text_box.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_text_box.o: /usr/include/sys/_types/_int8_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_int16_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_int32_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_int64_t.h
.o/wid_text_box.o: /usr/include/_types/_uint8_t.h
.o/wid_text_box.o: /usr/include/_types/_uint16_t.h
.o/wid_text_box.o: /usr/include/_types/_uint32_t.h
.o/wid_text_box.o: /usr/include/_types/_uint64_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_text_box.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_text_box.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_text_box.o: /usr/include/_types/_intmax_t.h
.o/wid_text_box.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/wid_text_box.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_text_box.o: /usr/include/sys/_types/_va_list.h
.o/wid_text_box.o: /usr/include/sys/_types/_size_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_text_box.o: /usr/include/sys/_types/_off_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_text_box.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_text_box.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/wid_text_box.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h
.o/wid_text_box.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/wid_text_box.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_text_box.o: /usr/include/sys/_types/_clock_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_time_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_text_box.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_text_box.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_text_box.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_text_box.o: my_wid_text_box.h my_wid.h my_wid_tiles.h my_tile.h
.o/wid_text_box.o: my_tex.h my_gl.h my_color.h my_point.h my_math.h
.o/wid_text_box.o: /usr/include/math.h my_size.h my_ttf.h my_font.h
.o/wid_text_box.o: my_ascii.h
.o/wid_tiles.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_tiles.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid_tiles.o: /usr/include/sys/_posix_availability.h
.o/wid_tiles.o: /usr/include/Availability.h
.o/wid_tiles.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_tiles.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_tiles.o: /usr/include/i386/_types.h
.o/wid_tiles.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_tiles.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_tiles.o: /usr/include/sys/_types/_int8_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_int16_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_int32_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_int64_t.h
.o/wid_tiles.o: /usr/include/_types/_uint8_t.h
.o/wid_tiles.o: /usr/include/_types/_uint16_t.h
.o/wid_tiles.o: /usr/include/_types/_uint32_t.h
.o/wid_tiles.o: /usr/include/_types/_uint64_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_tiles.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_tiles.o: /usr/include/_types/_intmax_t.h
.o/wid_tiles.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/wid_tiles.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_tiles.o: /usr/include/sys/_types/_va_list.h
.o/wid_tiles.o: /usr/include/sys/_types/_size_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_tiles.o: /usr/include/sys/_types/_off_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_tiles.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_tiles.o: my_array_bounds_check.h my_vector_bounds_check.h
.o/wid_tiles.o: c_plus_plus_serializer.h my_ptrcheck.h my_sdl.h my_command.h
.o/wid_tiles.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid_tiles.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_tiles.o: /usr/include/sys/_types/_clock_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_time_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_tiles.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_tiles.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_tiles.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_tiles.o: my_gl.h my_color.h my_point.h my_math.h /usr/include/math.h
.o/wid_tiles.o: my_wid_tiles.h my_tile.h my_tex.h
