/*
    This file is part of vapminer.

    vapminer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    vapminer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with vapminer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "VapashAux.h"

#include <vapash/vapash.hpp>

using namespace dev;
using namespace vap;

Result VapashAux::eval(int epoch, h256 const& _headerHash, uint64_t _nonce) noexcept
{
    auto headerHash = vapash::hash256_from_bytes(_headerHash.data());
    auto& context = vapash::get_global_epoch_context(epoch);
    auto result = vapash::hash(context, headerHash, _nonce);
    h256 mix{reinterpret_cast<byte*>(result.mix_hash.bytes), h256::ConstructFromPointer};
    h256 final{reinterpret_cast<byte*>(result.final_hash.bytes), h256::ConstructFromPointer};
    return {final, mix};
}