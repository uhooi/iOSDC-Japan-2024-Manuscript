REVIEW_VERSION := 5.9
REVIEW_CONFIG_FILE ?= config.yml
REVIEW_OUTPUT_TYPE ?= pdf
REVIEW_BOOKNAME := iOSDC-Japan-2024-Manuscript

.PHONY: setup
setup:
	$(MAKE) install-ruby
	$(MAKE) install-gems

.PHONY: install-ruby
install-ruby:
	cat .ruby-version | xargs rbenv install --skip-existing

.PHONY: install-gems
install-gems:
	bundle config path vendor/bundle
	bundle install --jobs 4 --retry 3

.PHONY: update-gems
update-gems:
	bundle config path vendor/bundle
	bundle update --jobs 4 --retry 3

.PHONY: build-paper
build-paper:
	$(MAKE) build

.PHONY: build-ebook
build-ebook:
	$(MAKE) build REVIEW_CONFIG_FILE=config-ebook.yml

.PHONY: build-epub
build-epub:
	$(MAKE) build REVIEW_OUTPUT_TYPE=epub

.PHONY: build
build:
	docker run -t --rm -v ${PWD}:/book vvakame/review:${REVIEW_VERSION} /bin/bash -ci "cd /book && ./setup.sh && REVIEW_CONFIG_FILE=${REVIEW_CONFIG_FILE} npm run ${REVIEW_OUTPUT_TYPE}"
	$(MAKE) open

.PHONY: open
open:
	open ./articles/${REVIEW_BOOKNAME}.${REVIEW_OUTPUT_TYPE}
