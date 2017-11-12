/* Copyright 2017 Tymoteusz Blazejczyk
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "logic/axi4/stream/reset_sequence_item.hpp"

#include <scv.h>

using logic::axi4::stream::reset_sequence_item;

reset_sequence_item::reset_sequence_item() :
    reset_sequence_item{"reset_sequence_item"}
{ }

reset_sequence_item::reset_sequence_item(const std::string& name) :
    uvm::uvm_sequence_item{name},
    duration{},
    idle{}
{ }

void reset_sequence_item::randomize() {
    scv_smart_ptr<std::size_t> random_value;

    random_value->keep_only(1, 4);
    random_value->next();

    duration = *random_value;

    random_value->reset_distribution();
    random_value->keep_only(0, 3);
    random_value->next();

    idle = *random_value;
}

std::string reset_sequence_item::convert2string() const {
    std::ostringstream ss;
    ss << "duration: " << duration <<
        ", idle: " << idle;
    return ss.str();
}

reset_sequence_item::~reset_sequence_item() { }

void reset_sequence_item::do_print(const uvm::uvm_printer& printer) const {
    printer.print_field_int("duration",
            duration, 8 * sizeof(std::size_t));

    printer.print_field_int("idle",
            idle, 8 * sizeof(std::size_t));
}

void reset_sequence_item::do_pack(uvm::uvm_packer& p) const {
    p << duration;
}

void reset_sequence_item::do_unpack(uvm::uvm_packer& p) {
    p >> duration;
}

void reset_sequence_item::do_copy(const uvm::uvm_object& rhs) {
    auto other = dynamic_cast<const reset_sequence_item*>(&rhs);
    if (other) {
        *this = *other;;
    }
    else {
        UVM_ERROR(get_name(), "Error in do_copy");
    }
}

bool reset_sequence_item::do_compare(const uvm::uvm_object& rhs,
        const uvm::uvm_comparer* /* comparer */) const {
    auto other = dynamic_cast<const reset_sequence_item*>(&rhs);
    auto status = false;

    if (other) {
        status = (duration == other->duration) &&
            (idle == other->idle);
    }
    else {
        UVM_ERROR(get_name(), "Error in do_compare");
    }

    return status;
}