FROM quay.io/school21/alpine:3.16
RUN apk --no-cache --upgrade add gcc make cppcheck g++ valgrind check check-dev gtest-dev
CMD ["make", "valgrind"]