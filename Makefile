.PHONY: container build pack distrib clean

bazel-image:
	docker build --no-cache -t ubuntu-bazel:1.0 -f docker/Dockerfile.builder .

build-plugins:
	docker run --rm --name smartspeech-plugins-builder -t -v ${PWD}:/src -v bazel-root:/bazel-root -w /src ubuntu-bazel:1.0 package/build-plugins.sh

unimrcp-image:
	docker build --no-cache -t unimrcp:1.7 -f docker/Dockerfile.runner .

start-test-server:
	docker run --rm -it --name smartspeech-unimrcp-server -v ${PWD}:/src -w /src --env-file .env unimrcp:1.7 package/start-unimrcp.sh

run-test-synth:
	docker run

run-test-recognize:
	docker run

clean:
	rm -rf bazel-*
	rm -rf output


