// RUN: %clang_cc1 -triple x86_64-apple-macosx10.9.0 -emit-llvm -main-file-name cxx-linkage.cpp %s -o - -fprofile-instr-generate | FileCheck %s

// CHECK: @__llvm_pgo_counters__Z3foov = global [1 x i64] zeroinitializer, section "__DATA,__llvm_pgo_cnts", align 8
// CHECK: @__llvm_pgo_name__Z3foov = constant [7 x i8] c"_Z3foov", section "__DATA,__llvm_pgo_names", align 1
// CHECK: @__llvm_pgo_data__Z3foov = constant { i32, i32, i8*, i64* } { i32 7, i32 1, i8* bitcast ([7 x i8]* @__llvm_pgo_name__Z3foov to i8*), i64* bitcast ([1 x i64]* @__llvm_pgo_counters__Z3foov to i64*) }, section "__DATA,__llvm_pgo_data", align 8
void foo(void) { }

// CHECK: @__llvm_pgo_counters__Z8foo_weakv = weak global [5 x i64] zeroinitializer, section "__DATA,__llvm_pgo_cnts", align 8
// CHECK: @__llvm_pgo_name__Z8foo_weakv = weak constant [12 x i8] c"_Z8foo_weakv", section "__DATA,__llvm_pgo_names", align 1
// CHECK: @__llvm_pgo_data__Z8foo_weakv = weak constant { i32, i32, i8*, i64* } { i32 12, i32 5, i8* bitcast ([12 x i8]* @__llvm_pgo_name__Z8foo_weakv to i8*), i64* bitcast ([5 x i64]* @__llvm_pgo_counters__Z8foo_weakv to i64*) }, section "__DATA,__llvm_pgo_data", align 8
void foo_weak(void) __attribute__((weak));
void foo_weak(void) { if (0){} if (0){} if (0){} if (0){} }

// CHECK: @__llvm_pgo_counters_main = global [1 x i64] zeroinitializer, section "__DATA,__llvm_pgo_cnts", align 8
// CHECK: @__llvm_pgo_name_main = constant [4 x i8] c"main", section "__DATA,__llvm_pgo_names", align 1
// CHECK: @__llvm_pgo_data_main = constant { i32, i32, i8*, i64* } { i32 4, i32 1, i8* bitcast ([4 x i8]* @__llvm_pgo_name_main to i8*), i64* bitcast ([1 x i64]* @__llvm_pgo_counters_main to i64*) }, section "__DATA,__llvm_pgo_data", align 8
inline void foo_inline(void);
int main(void) {
  foo();
  foo_inline();
  foo_weak();
  return 0;
}

// CHECK: @__llvm_pgo_counters__Z10foo_inlinev = linkonce_odr global [7 x i64] zeroinitializer, section "__DATA,__llvm_pgo_cnts", align 8
// CHECK: @__llvm_pgo_name__Z10foo_inlinev = linkonce_odr constant [15 x i8] c"_Z10foo_inlinev", section "__DATA,__llvm_pgo_names", align 1
// CHECK: @__llvm_pgo_data__Z10foo_inlinev = linkonce_odr constant { i32, i32, i8*, i64* } { i32 15, i32 7, i8* bitcast ([15 x i8]* @__llvm_pgo_name__Z10foo_inlinev to i8*), i64* bitcast ([7 x i64]* @__llvm_pgo_counters__Z10foo_inlinev to i64*) }, section "__DATA,__llvm_pgo_data", align 8
inline void foo_inline(void) { if (0){} if (0){} if (0){} if (0){} if (0){} if (0){}}

// CHECK: @llvm.used = appending global [4 x i8*] [i8* bitcast ({ i32, i32, i8*, i64* }* @__llvm_pgo_data__Z3foov to i8*), i8* bitcast ({ i32, i32, i8*, i64* }* @__llvm_pgo_data__Z8foo_weakv to i8*), i8* bitcast ({ i32, i32, i8*, i64* }* @__llvm_pgo_data_main to i8*), i8* bitcast ({ i32, i32, i8*, i64* }* @__llvm_pgo_data__Z10foo_inlinev to i8*)], section "llvm.metadata"
