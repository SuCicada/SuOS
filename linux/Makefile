build: suos.img
	@echo over
output/suos.bin : suos.nas Makefile output
	#bin/nask.exe $< $@ suos.lst
	nasm -o $@ $<   
output/suos.img : output/suos.bin Makefile output
	bin/edimg.sh $< $@
run: output/suos.img 
	qemu-system-x86_64 -drive file=$<,if=floppy
output: 
	mkdir output
.PHONY: list
list:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'
clean:
	@rm -r output

