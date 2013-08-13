TARGET_DIRS := src

define build_obj
for sub_dir in $(TARGET_DIRS); do \
	echo "Building in $$sub_dir ..."; \
	make -C $$sub_dir; \
done
endef

all:
	@$(call build_obj)
	g++ -o ./obj/leetcode ./obj/*.o

clean:
	-rm ./obj/*.o ./obj 
	
