install: suos.img
	@echo over
suos.bin : suos.nas Makefile
	bin/nask.exe $< $@ suos.lst
        
suos.img : suos.bin Makefile
	bin/edimg.exe imgin:bin/fdimg0at.tek \
    wbinimg src:$< len:512 from:0 to:0 \
    imgout:img/$@
.PHONY: list
list:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'
clean:
	@rm -f suos.bin suos.lst img/suos.img
